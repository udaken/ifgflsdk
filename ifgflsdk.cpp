#include "stdafx.h"
#include "libgfl.h"
#include "susie.hpp"
#include <cstdlib>
#include <cstring>
#include "gfl.hpp"
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

SPI_RESULT gflErrorToSpiResult(GflError error) noexcept
{
	switch (error)
	{
	case GflError::NoError:
		return SPI_RESULT::SPI_ALL_RIGHT;
	case GflError::FileOpen: case GflError::FileRead:
		return SPI_RESULT::SPI_FILE_READ_ERROR;
	case GflError::FileCreate: case GflError::FileWrite:
		return SPI_RESULT::SPI_FILE_WRITE_ERROR;
	case GflError::NoMemory:
		return SPI_RESULT::SPI_MEMORY_ERROR;
	case GflError::UnknownFormat: case GflError::BadFormatIndex:
		return SPI_RESULT::SPI_NOT_SUPPORT;
	case GflError::BadBitmap:
		return SPI_RESULT::SPI_OUT_OF_ORDER;
	case GflError::BadParameters:
		return SPI_RESULT::SPI_OTHER_ERROR;
	case GflError::UnknownError: default:
		return SPI_RESULT::SPI_NO_FUNCTION;
	}
}

int WINAPI GetPluginInfo(int32_t infono, LPSTR  buf, int32_t buflen) noexcept
{
	try
	{
		GflLibraryInit init;

		switch (infono)
		{
		case 0:
			return (::strcpy_s(buf, buflen, "00IN")) == 0 ? std::strlen(buf) : 0;
		case 1:
		{
			return (::strcpy_s(buf, buflen, ("GFL SDK " + std::string(::gflGetVersion())).c_str())) == 0 ? std::strlen(buf) : 0;
		}
		}

		auto index = infono / 2;
		auto isdescription = infono % 2;
		if (isdescription)
		{
			auto s = ::gflGetFormatDescriptionByIndex(index);
			if (s == nullptr) return 0;
			::strcpy_s(buf, buflen, s);
		}
		else
		{
			auto extName = ::gflGetDefaultFormatSuffixByIndex(index);
			if (extName == nullptr) return 0;
			::strcpy_s(buf, buflen, (std::string("*.") + extName).c_str());
		}
		return std::strlen(buf);
	}
	catch (const GflException & /*e*/)
	{
		return 0;
	}
	catch (const std::exception &e)
	{
		return 0;
	}
}
BOOL WINAPI IsSupported(LPCSTR filename, void* dw) noexcept
{
	try
	{
		GflLibraryInit init;
		{
			//BYTE buff[2048];
			if ((DWORD_PTR)dw & ~(DWORD_PTR)0xffff) { // 2K メモリイメージ
			}
			else { // ファイルハンドル
			}

			auto ext = ::PathFindExtensionA(filename);
			if (ext)
			{
				auto formats = GflFormats::getReadableFormats();
				for (auto& f : formats)
				{
					for (UINT i = 0; i < f.NumberOfExtension; i++)
					{
						if (::PathMatchSpecA(filename, (std::string("*.") + f.Extension[i]).c_str()))
							return TRUE;
					}
				}
			}
			return FALSE;
		}
	}
	catch (const GflException &/*e*/)
	{
		return FALSE;
	}
	catch (const std::exception &e)
	{
		return FALSE;
	}
}
SPI_RESULT WINAPI GetPictureInfo(LPCSTR  buf, size_t len, SPI_FLAG flag, SUSIE_PICTUREINFO* lpInfo) noexcept
{
	try
	{
		GflLibraryInit init;
		{
			GflInfomation fileInfo;
			if ((flag & SPI_FLAG::SPI_INPUT_MASK) == SPI_FLAG::SPI_INPUT_MEMORY)
			{
				auto e = ::gflGetFileInformationFromMemory(reinterpret_cast<const BYTE*>(buf), len, -1, &fileInfo);
				if (e != GFL_NO_ERROR)
					return gflErrorToSpiResult(static_cast<GflError>(e));
			}
			else if ((flag & SPI_FLAG::SPI_INPUT_MASK) == SPI_FLAG::SPI_INPUT_FILE)
			{
				auto e = ::gflGetFileInformation(buf, -1, &fileInfo);
				if (e != GFL_NO_ERROR)
					return gflErrorToSpiResult(static_cast<GflError>(e));
			}
			else
			{
				return SPI_RESULT::SPI_NO_FUNCTION;
			}
			*lpInfo = SUSIE_PICTUREINFO();
			lpInfo->height = fileInfo.Height;
			lpInfo->width = fileInfo.Width;
			lpInfo->x_density = fileInfo.Xdpi;
			lpInfo->y_density = fileInfo.Ydpi;
			lpInfo->colorDepth = fileInfo.BitsPerComponent * fileInfo.ComponentsPerPixel;

			return SPI_RESULT::SPI_ALL_RIGHT;
		}
	}
	catch (const GflException &e)
	{
		return gflErrorToSpiResult(e.code());
	}
	catch (const std::exception &e)
	{
		return SPI_NO_FUNCTION;
	}
}

SPI_RESULT WINAPI GetPicture(LPCSTR  buf, size_t len, SPI_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PROGRESS progressCallback, intptr_t lData) noexcept
{
	try
	{
		GflLibraryInit init;
		{
			GflLoadParam load_params;
			load_params.Origin = GFL_BOTTOM_LEFT;
			load_params.ColorModel = GFL_BGRA;

			GFL_BITMAP *ptr = nullptr;
			GflInfomation fileInfo;
			if ((flag & SPI_FLAG::SPI_INPUT_MASK) == SPI_FLAG::SPI_INPUT_MEMORY)
			{
				auto e = ::gflLoadBitmapFromMemory(reinterpret_cast<const BYTE*>(buf), len, &ptr, &load_params, &fileInfo);
				if (e != GFL_NO_ERROR)
					return gflErrorToSpiResult(static_cast<GflError>(e));
			}
			else if ((flag & SPI_FLAG::SPI_INPUT_MASK) == SPI_FLAG::SPI_INPUT_FILE)
			{
				if (len != 0)
					return SPI_NO_FUNCTION;

				auto e = ::gflLoadBitmap(buf, &ptr, &load_params, &fileInfo);
				if(e != GFL_NO_ERROR)
					return gflErrorToSpiResult(static_cast<GflError>(e));
			}
			else
			{
				return SPI_NO_FUNCTION;
			}

			const GflBitmapPtr pBitmap(ptr);
			std::unique_ptr<BITMAPINFOHEADER, decltype(&::LocalFree)> pBInfo(static_cast<BITMAPINFOHEADER*>(::LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * pBitmap->ColorUsed )), &::LocalFree);

			if (!pBInfo)
				return SPI_NO_MEMORY;

			switch (pBitmap->Type)
			{
			case GFL_GREY:
			case GFL_BGRA:
			case GFL_BGR:
				break;
			default:
				assert(false);
				return SPI_NOT_SUPPORT;
			}

			*pBInfo = BITMAPINFOHEADER({
				sizeof(BITMAPINFOHEADER),
				fileInfo.Width,
				(pBitmap->Origin & GFL_BOTTOM ? 1 : -1) * fileInfo.Height,
				1,
				static_cast<WORD>(pBitmap->BitsPerComponent * pBitmap->ComponentsPerPixel),
				BI_RGB,
				pBitmap->BytesPerLine * fileInfo.Height,
				1,
				1,
				static_cast<DWORD>(pBitmap->ColorUsed),
				});

			RGBQUAD *colorTable = reinterpret_cast<RGBQUAD*>(pBInfo.get() + 1);

			if (pBitmap->ColorMap)
				std::memcpy(colorTable, pBitmap->ColorMap, sizeof(RGBQUAD) * pBitmap->ColorUsed);
			else if (pBitmap->Type == GFL_GREY)
			{
				for (UINT i = 0; i < pBitmap->ColorUsed; i++)
				{
					colorTable[i].rgbBlue = colorTable[i].rgbGreen = colorTable[i].rgbRed = static_cast<BYTE>(i);
				}
			}


			std::unique_ptr<void, decltype(&::LocalFree)> pBm(::LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, pBInfo->biSizeImage), &::LocalFree);
			if (!pBm)
				return SPI_NO_MEMORY;

			std::memcpy(pBm.get(), pBitmap->Data, pBInfo->biSizeImage);

			*pHBInfo = pBInfo.release();
			*pHBm = pBm.release();

			return SPI_ALL_RIGHT;
		}
	}
	catch (const GflException &e)
	{
		return gflErrorToSpiResult(e.code());
	}
	catch (const std::exception &e)
	{
		return SPI_NO_FUNCTION;
	}
}

SPI_RESULT WINAPI GetPreview(LPCSTR  buf, size_t len, SPI_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PROGRESS progressCallback, intptr_t lData)
{
	return SPI_NO_FUNCTION;
}
