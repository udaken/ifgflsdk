#pragma once
#include "libgfl.h"
#include <vector>
#include <memory>
#include <cassert>

//#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#define LWSTDAPI_(type)   EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
LWSTDAPI_(BOOL)     PathMatchSpecA(__in LPCSTR pszFile, __in LPCSTR pszSpec);
LWSTDAPI_(BOOL)     PathMatchSpecW(__in LPCWSTR pszFile, __in LPCWSTR pszSpec);
LWSTDAPI_(BOOL)     PathRemoveFileSpecA(__inout LPSTR pszPath);
LWSTDAPI_(BOOL)     PathRemoveFileSpecW(__inout LPWSTR pszPath);
LWSTDAPI_(LPSTR)  PathCombineA(__out_ecount(MAX_PATH) LPSTR pszDest, __in_opt LPCSTR pszDir, __in_opt LPCSTR pszFile);
LWSTDAPI_(LPWSTR)  PathCombineW(__out_ecount(MAX_PATH) LPWSTR pszDest, __in_opt LPCWSTR pszDir, __in_opt LPCWSTR pszFile);
LWSTDAPI_(BOOL)     PathAppendA(__inout_ecount(MAX_PATH) LPSTR pszPath, __in LPCSTR pMore);
LWSTDAPI_(BOOL)     PathAppendW(__inout_ecount(MAX_PATH) LPWSTR pszPath, __in LPCWSTR pMore);

enum class GflError : GFL_INT16
{
	NoError = GFL_NO_ERROR,
	FileOpen = GFL_ERROR_FILE_OPEN,
	FileRead = GFL_ERROR_FILE_READ,
	FileCreate = GFL_ERROR_FILE_CREATE,
	FileWrite = GFL_ERROR_FILE_WRITE,
	NoMemory = GFL_ERROR_NO_MEMORY,
	UnknownFormat = GFL_ERROR_UNKNOWN_FORMAT,
	BadBitmap = GFL_ERROR_BAD_BITMAP,
	BadFormatIndex = GFL_ERROR_BAD_FORMAT_INDEX,
	BadParameters = GFL_ERROR_BAD_PARAMETERS,
	UnknownError = GFL_UNKNOWN_ERROR,
};

class GflException : public std::exception
{
private:
	const GflError error;
public:
	explicit GflException(GFL_ERROR error) noexcept
		: GflException(static_cast<GflError>(error))
	{};
	GflException(GflError error) noexcept
		: error(error)
	{};
	GflError code() const noexcept
	{
		return error;
	}
};

inline void GlfCheckError(GFL_ERROR code)
{
	assert(GFL_NO_ERROR == code);

	if (code != GFL_NO_ERROR)
		throw GflException(code);
}

class GflLibrary final
{
public:
	GflLibrary() noexcept
	{
		if (g_hModule)
		{
			WCHAR buf[MAX_PATH] = {};
			::GetModuleFileName(g_hModule, buf, _countof(buf));
			::PathRemoveFileSpecW(buf);
			::PathAppendW(buf, L"libgfl340.dll");
			hLibgfl = ::LoadLibrary(buf);
		}

		if (hLibgfl)
		{
#define GETPROCADDRESS(hModule, _f) reinterpret_cast<decltype(&_f)>(::GetProcAddress(hLibgfl, #_f))
			LibraryInit = GETPROCADDRESS(hLibgfl, gflLibraryInit);
			LibraryExit = GETPROCADDRESS(hLibgfl, gflLibraryExit);
			EnableLZW = GETPROCADDRESS(hLibgfl, gflEnableLZW);
			FreeFileInformation = GETPROCADDRESS(hLibgfl, gflFreeFileInformation);
			GetFormatInformationByIndex = GETPROCADDRESS(hLibgfl, gflGetFormatInformationByIndex);
			FormatIsReadableByIndex = GETPROCADDRESS(hLibgfl, gflFormatIsReadableByIndex);
			GetNumberOfFormat = GETPROCADDRESS(hLibgfl, gflGetNumberOfFormat);
			FreeBitmap = GETPROCADDRESS(hLibgfl, gflFreeBitmap);
			GetDefaultLoadParams = GETPROCADDRESS(hLibgfl, gflGetDefaultLoadParams);
			GetVersion = GETPROCADDRESS(hLibgfl, gflGetVersion);
			GetFormatDescriptionByIndex = GETPROCADDRESS(hLibgfl, gflGetFormatDescriptionByIndex);
			GetDefaultFormatSuffixByIndex = GETPROCADDRESS(hLibgfl, gflGetDefaultFormatSuffixByIndex);
			GetFileInformationFromMemory = GETPROCADDRESS(hLibgfl, gflGetFileInformationFromMemory);
			GetFileInformation = GETPROCADDRESS(hLibgfl, gflGetFileInformation);
			LoadBitmapFromMemory = GETPROCADDRESS(hLibgfl, gflLoadBitmapFromMemory);
			LoadBitmap = GETPROCADDRESS(hLibgfl, gflLoadBitmap);
#undef GETPROCADDRESS
		}
	}
	~GflLibrary() noexcept
	{
		if (hLibgfl)
			::FreeLibrary(hLibgfl);
	}
	bool isLoaded() const  noexcept
	{
		return hLibgfl != nullptr;
	}
	decltype(::gflLibraryInit) *LibraryInit = nullptr;
	decltype(::gflLibraryExit) *LibraryExit = nullptr;
	decltype(::gflEnableLZW) *EnableLZW = nullptr;
	decltype(::gflFreeFileInformation) *FreeFileInformation = nullptr;
	decltype(::gflGetFormatInformationByIndex) *GetFormatInformationByIndex = nullptr;
	decltype(::gflFormatIsReadableByIndex) *FormatIsReadableByIndex = nullptr;
	decltype(::gflGetNumberOfFormat) *GetNumberOfFormat = nullptr;
	decltype(::gflFreeBitmap) *FreeBitmap = nullptr;
	decltype(::gflGetDefaultLoadParams) *GetDefaultLoadParams = nullptr;
	decltype(::gflGetVersion) *GetVersion = nullptr;
	decltype(::gflGetFormatDescriptionByIndex) *GetFormatDescriptionByIndex = nullptr;
	decltype(::gflGetDefaultFormatSuffixByIndex) *GetDefaultFormatSuffixByIndex = nullptr;
	decltype(::gflGetFileInformationFromMemory) *GetFileInformationFromMemory = nullptr;
	decltype(::gflGetFileInformation) *GetFileInformation = nullptr;
	decltype(::gflLoadBitmapFromMemory) *LoadBitmapFromMemory = nullptr;
	decltype(::gflLoadBitmap) *LoadBitmap = nullptr;
private:
	HMODULE hLibgfl = nullptr;
};

class GflFormats
{
private:
	template <class Predicate>
	static std::vector<GFL_FORMAT_INFORMATION> getFormats(const GflLibrary & lib, Predicate pred)
	{
		auto n = lib.GetNumberOfFormat();
		std::vector<GFL_FORMAT_INFORMATION> formats(n);
		for (auto i = 0; i < n; i++)
		{
			if (pred(i))
			{
				GFL_FORMAT_INFORMATION info;
				auto result = lib.GetFormatInformationByIndex(i, &info);
				GlfCheckError(result);
				formats.emplace_back(info);
			}
		}
		return formats;

	}
public:
	static std::vector<GFL_FORMAT_INFORMATION> getAllFormats(const GflLibrary & lib)
	{
		return getFormats(lib, [](auto) { return true; });
	}
	static std::vector<GFL_FORMAT_INFORMATION> getReadableFormats(const GflLibrary & lib)
	{
		return getFormats(lib, [&](auto i) { return lib.FormatIsReadableByIndex(i); });
	}
};

class GflLibraryInit final
{
public:
	GflLibraryInit(const GflLibrary & lib, bool enableLzw = true) : lib(lib)
	{
		if (lib.isLoaded())
		{
			auto result = lib.LibraryInit();
			GlfCheckError(result);
			if (enableLzw)
				lib.EnableLZW(GFL_TRUE);
		}
	}
	~GflLibraryInit()
	{
		if (lib.isLoaded())
			lib.LibraryExit();
	}
private:
	const GflLibrary & lib;
};

class GflInfomation final : public GFL_FILE_INFORMATION
{
private:
	bool hadFree = false;
public:
	GflInfomation(const GflLibrary & lib) : lib(lib), GFL_FILE_INFORMATION() {}
	GflInfomation(GflInfomation && other) : lib(other.lib), GFL_FILE_INFORMATION(other)
	{
		std::swap(hadFree, other.hadFree);
	}
	void free()
	{
		if (!hadFree)
		{
			lib.FreeFileInformation(this);
			hadFree = true;
		}

	}
	~GflInfomation()
	{
		if (!hadFree)
			lib.FreeFileInformation(this);
	}
private:
	const GflLibrary & lib;
};

struct GflBitmapDeleter
{
	GflBitmapDeleter(const GflLibrary & lib) : lib(lib) {}
	void operator()(GFL_BITMAP* ptr) {
		lib.FreeBitmap(ptr);
	}
private:
	const GflLibrary & lib;
};

typedef std::unique_ptr<GFL_BITMAP, GflBitmapDeleter> GflBitmapPtr;

inline GflBitmapPtr GflMakeBitmapPtr(const GflLibrary & lib, GFL_BITMAP *&ptr) noexcept
{
	return { std::exchange(ptr, nullptr), GflBitmapDeleter(lib) };
}

class GflLoadParam final : public GFL_LOAD_PARAMS
{
public:
	GflLoadParam(const GflLibrary & lib) : lib(lib)
	{
		lib.GetDefaultLoadParams(this);
	}
private:
	const GflLibrary & lib;
};