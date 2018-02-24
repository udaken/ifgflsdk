#include "stdafx.h"
#include <cstdlib>
#include <cstring>
#include <type_traits>
#include <limits>
#include <string>
#include <mutex>

#include "libgfl.h"
#include "susie.hpp"

#include "gfl.hpp"

using namespace std::string_literals;

std::once_flag once;
std::shared_ptr<GflLibrary> g_lib;

static void initGflLib()
{
	if (!g_lib)
		g_lib.reset(new GflLibrary);
}

constexpr inline SUSIE_RESULT GflErrorToSpiResult(GflError error) noexcept
{
	switch (error)
	{
	case GflError::NoError:
		return SUSIE_RESULT::ALL_RIGHT;
	case GflError::FileOpen: case GflError::FileRead:
		return SUSIE_RESULT::FILE_READ_ERROR;
	case GflError::FileCreate: case GflError::FileWrite:
		return SUSIE_RESULT::FILE_WRITE_ERROR;
	case GflError::NoMemory:
		return SUSIE_RESULT::MEMORY_ERROR;
	case GflError::UnknownFormat: case GflError::BadFormatIndex:
		return SUSIE_RESULT::NOT_SUPPORT;
	case GflError::BadBitmap:
		return SUSIE_RESULT::OUT_OF_ORDER;
	case GflError::BadParameters:
		return SUSIE_RESULT::OTHER_ERROR;
	case GflError::UnknownError: default:
		return SUSIE_RESULT::NO_FUNCTION;
	}
}
template <class F>
constexpr inline F bitwiseOr(F a, F b) noexcept
{
	return static_cast<F>(static_cast<typename std::underlying_type<F>::type>(a) | static_cast<typename std::underlying_type<F>::type>(b));
}

template <class F>
constexpr inline F bitwiseAnd(F a, F b) noexcept
{
	return static_cast<F>(static_cast<typename std::underlying_type<F>::type>(a) & static_cast<typename std::underlying_type<F>::type>(b));
}

int32_t WINAPI GetPluginInfo(int32_t infono, LPSTR  buf, int32_t buflen) noexcept
{
	std::call_once(once, initGflLib);

	try
	{
		GflLibraryInit init(*g_lib);

		switch (infono)
		{
		case 0:
		{
			if ((::strcpy_s(buf, buflen, "00IN")) != 0)
				return 0;
			return static_cast<int>(std::strlen(buf));
		}
		case 1:
		{
			if ((::strcpy_s(buf, buflen, ("ifgsldk: 0.1, GFL SDK: "s
				+ (g_lib->isLoaded() ? g_lib->GetVersion() : "Not installed.")).c_str())) != 0)
				return 0;
			return static_cast<int>(std::strlen(buf));
		}
		}

		if (!g_lib->isLoaded()) return 0;

		auto index = infono / 2;
		auto isdescription = infono % 2;
		if (isdescription)
		{
			auto s = g_lib->GetFormatDescriptionByIndex(index);
			if (s == nullptr) return 0;
			::strcpy_s(buf, buflen, s);
		}
		else
		{
			auto extName = g_lib->GetDefaultFormatSuffixByIndex(index);
			if (extName == nullptr) return 0;
			::strcpy_s(buf, buflen, ("*."s + extName).c_str());
		}
		return static_cast<int>(std::strlen(buf));
	}
	catch (const GflException & /* e */)
	{
		return 0;
	}
	catch (const std::exception &/* e */)
	{
		return 0;
	}
}
BOOL WINAPI IsSupported(LPCSTR filename, void* dw) noexcept
{
	std::call_once(once, initGflLib);

	if (!g_lib->isLoaded()) return FALSE;
	try
	{
		GflLibraryInit init(*g_lib);
		{
			//BYTE buff[2048];
			if ((DWORD_PTR)dw & ~(DWORD_PTR)0xffff) { // 2K メモリイメージ
			}
			else { // ファイルハンドル
			}

			auto formats = GflFormats::getReadableFormats(*g_lib);
			for (auto& f : formats)
			{
				for (UINT i = 0; i < f.NumberOfExtension; i++)
				{
					if (::PathMatchSpecA(filename, ("*."s + f.Extension[i]).c_str()))
						return TRUE;
				}
			}
			return FALSE;
		}
	}
	catch (const GflException &/*e*/)
	{
		return FALSE;
	}
	catch (const std::exception &/*e*/)
	{
		return FALSE;
	}
}
SUSIE_RESULT WINAPI GetPictureInfo(LPCSTR  buf, size_t len, SUSIE_FLAG flag, SUSIE_PICTUREINFO* lpInfo) noexcept
{
	std::call_once(once, initGflLib);

	if (!g_lib->isLoaded()) return SUSIE_RESULT::OTHER_ERROR;
	try
	{
		GflLibraryInit init(*g_lib);
		{
			GflInfomation fileInfo(*g_lib);
			if (bitwiseAnd(flag, SUSIE_FLAG::SPI_INPUT_MASK) == SUSIE_FLAG::SPI_INPUT_MEMORY)
			{
				if (std::numeric_limits<decltype(len)>::max() > std::numeric_limits<GFL_UINT32>::max())
				{
					return SUSIE_RESULT::MEMORY_ERROR;
				}
				auto e = g_lib->GetFileInformationFromMemory(reinterpret_cast<const BYTE*>(buf), static_cast<GFL_UINT32>(len), -1, &fileInfo);
				if (e != GFL_NO_ERROR)
					return GflErrorToSpiResult(static_cast<GflError>(e));
			}
			else if (bitwiseAnd(flag, SUSIE_FLAG::SPI_INPUT_MASK) == SUSIE_FLAG::SPI_INPUT_FILE)
			{
				auto e = g_lib->GetFileInformation(buf, -1, &fileInfo);
				if (e != GFL_NO_ERROR)
					return GflErrorToSpiResult(static_cast<GflError>(e));
			}
			else
			{
				return SUSIE_RESULT::NO_FUNCTION;
			}
			*lpInfo = {};
			lpInfo->height = fileInfo.Height;
			lpInfo->width = fileInfo.Width;
			lpInfo->x_density = fileInfo.Xdpi;
			lpInfo->y_density = fileInfo.Ydpi;
			lpInfo->colorDepth = fileInfo.BitsPerComponent * fileInfo.ComponentsPerPixel;

			return SUSIE_RESULT::ALL_RIGHT;
		}
	}
	catch (const GflException &e)
	{
		return GflErrorToSpiResult(e.code());
	}
	catch (const std::exception &/*e*/)
	{
		return SUSIE_RESULT::NO_FUNCTION;
	}
}
static void* GFLAPI allocator(GFL_INT32 width, GFL_INT32 height, GFL_INT32 number_component, GFL_INT32 bits_per_component, GFL_INT32 padding, GFL_INT32 bytes_per_line, void * user_params)
{
	return reinterpret_cast<void*>(::LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, height * bytes_per_line));
}
SUSIE_RESULT WINAPI GetPicture(LPCSTR  buf, size_t len, SUSIE_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PROGRESS /* progressCallback */, intptr_t /* lData */) noexcept
{
	std::call_once(once, initGflLib);

	if (!g_lib->isLoaded()) return SUSIE_RESULT::OTHER_ERROR;
	try
	{
		GflLibraryInit init(*g_lib);
		{
			GflLoadParam load_params(*g_lib);
			load_params.Origin = GFL_BOTTOM_LEFT;
			load_params.ColorModel = GFL_BGRA;
			load_params.Callbacks.AllocateBitmap = allocator; //バグでAllocateBitmapは呼び出されない https://newsgroup.xnview.com/viewtopic.php?t=25369

			GFL_BITMAP *ptr = nullptr;
			if (bitwiseAnd(flag, SUSIE_FLAG::SPI_INPUT_MASK) == SUSIE_FLAG::SPI_INPUT_MEMORY)
			{
				if (std::numeric_limits<decltype(len)>::max() > std::numeric_limits<GFL_UINT32>::max())
				{
					return SUSIE_RESULT::MEMORY_ERROR;
				}
				auto e = g_lib->LoadBitmapFromMemory(reinterpret_cast<const BYTE*>(buf), static_cast<GFL_UINT32>(len), &ptr, &load_params, nullptr);
				if (e != GFL_NO_ERROR)
					return GflErrorToSpiResult(static_cast<GflError>(e));
			}
			else if (bitwiseAnd(flag, SUSIE_FLAG::SPI_INPUT_MASK) == SUSIE_FLAG::SPI_INPUT_FILE)
			{
				if (len != 0)
					return SUSIE_RESULT::NO_FUNCTION;

				auto e = g_lib->LoadBitmap(buf, &ptr, &load_params, nullptr);
				if (e != GFL_NO_ERROR)
					return GflErrorToSpiResult(static_cast<GflError>(e));
			}
			else
			{
				return SUSIE_RESULT::NO_FUNCTION;
			}

			{
				const GflBitmapPtr pBitmap = GflMakeBitmapPtr(*g_lib, ptr);
				std::unique_ptr<BITMAPINFOHEADER, decltype(&::LocalFree)> pBInfo(
					static_cast<BITMAPINFOHEADER*>(::LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * pBitmap->ColorUsed)), &::LocalFree);

				if (!pBInfo)
					return SUSIE_RESULT::SPI_NO_MEMORY;

				switch (pBitmap->Type)
				{
				case GFL_GREY:
				case GFL_COLORS:
				case GFL_BGRA:
				case GFL_BGR:
					break;
				default:
					assert(false);
					return SUSIE_RESULT::NOT_SUPPORT;
				}

				*pBInfo = {
					sizeof(BITMAPINFOHEADER),
					pBitmap->Width,
					(pBitmap->Origin & GFL_BOTTOM ? 1 : -1) * pBitmap->Height,
					1,
					static_cast<WORD>(pBitmap->BitsPerComponent * pBitmap->ComponentsPerPixel),
					BI_RGB,
					pBitmap->BytesPerLine * pBitmap->Height,
					1,
					1,
					static_cast<DWORD>(pBitmap->ColorUsed),
				};

				RGBQUAD *colorTable = reinterpret_cast<RGBQUAD*>(pBInfo.get() + 1);

				if (pBitmap->ColorMap)
				{
					for (INT i = 0; i < pBitmap->ColorUsed; i++)
					{
						colorTable[i].rgbBlue = pBitmap->ColorMap->Blue[i];
						colorTable[i].rgbRed = pBitmap->ColorMap->Red[i];
						colorTable[i].rgbGreen = pBitmap->ColorMap->Green[i];
					}
				}
				else if (pBitmap->Type == GFL_GREY)
				{
					for (INT i = 0; i < pBitmap->ColorUsed; i++)
					{
						colorTable[i].rgbBlue = colorTable[i].rgbGreen = colorTable[i].rgbRed = static_cast<BYTE>(i);
					}
				}

				typedef std::unique_ptr<void, decltype(&::LocalFree)> LocalPtr;
				LocalPtr pBm(nullptr, &::LocalFree);
				auto hLocal = init.DettachFromHeapManager(pBitmap->Data);
				if (hLocal)
				{
					pBm.reset(hLocal);
				}
				else
				{
					pBm.reset(::LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, pBInfo->biSizeImage));
					if (!pBm)
						return SUSIE_RESULT::SPI_NO_MEMORY;

					std::memcpy(pBm.get(), pBitmap->Data, pBInfo->biSizeImage);
				}
				*pHBInfo = pBInfo.release();
				*pHBm = pBm.release();

				return SUSIE_RESULT::ALL_RIGHT;
			}
		}
	}
	catch (const GflException &e)
	{
		return GflErrorToSpiResult(e.code());
	}
	catch (const std::exception & /*e*/)
	{
		return SUSIE_RESULT::NO_FUNCTION;
	}
}

SUSIE_RESULT WINAPI GetPreview(LPCSTR  buf, size_t len, SUSIE_FLAG flag, HLOCAL* pHBInfo, HLOCAL* pHBm, SUSIE_PROGRESS progressCallback, intptr_t lData)
{
	UNREFERENCED_PARAMETER(buf);
	UNREFERENCED_PARAMETER(len);
	UNREFERENCED_PARAMETER(flag);
	UNREFERENCED_PARAMETER(pHBInfo);
	UNREFERENCED_PARAMETER(pHBm);
	UNREFERENCED_PARAMETER(progressCallback);
	UNREFERENCED_PARAMETER(lData);
	return SUSIE_RESULT::NO_FUNCTION;
}
