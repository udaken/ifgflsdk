#pragma once
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>  

#include "libgfl.h"
#include <vector>
#include <memory>
#include <cassert>
#include <map>
#include <set>

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

#if defined(_DEBUG) || defined(DEBUG)
// Debugのとき
#define TRACE(x)   OutputDebugString(x)
#define TRACE0(x)   OutputDebugString(x)
#define TRACE1(x, a)            OutputDebugString(x, a)
#define TRACE2(x, a, b)         OutputDebugString(x, a, b)
#define TRACE3(x, a, b, c)      OutputDebugString(x, a, b, c)
#define TRACE4(x, a, b, c, d)   OutputDebugString(x, a, b, c, d)
#else
// Releaseのとき
#define TRACE(x)
#define TRACE0(x)
#define TRACE1(x, a)
#define TRACE2(x, a, b)
#define TRACE3(x, a, b, c)
#define TRACE4(x, a, b, c, d)
#endif

inline void OutputDebugStr(LPCSTR pszFormat, ...)
{
	va_list	argp;
	char pszBuf[256];
	va_start(argp, pszFormat);
	vsprintf_s(pszBuf, pszFormat, argp);
	va_end(argp);
	OutputDebugStringA(pszBuf);
}

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
		WCHAR buf[MAX_PATH] = {};
		if (g_hModule)
		{
			::GetModuleFileName(g_hModule, buf, _countof(buf));
			::PathRemoveFileSpecW(buf);
		}
		::PathAppendW(buf, L"libgfl340.dll");
		hLibgfl = ::LoadLibrary(buf);

		if (hLibgfl)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#define GETPROCADDRESS(hModule, _f) reinterpret_cast<decltype(&_f)>(::GetProcAddress(hLibgfl, #_f))
			LibraryInit = GETPROCADDRESS(hLibgfl, gflLibraryInit);
			LibraryInitEx = GETPROCADDRESS(hLibgfl, gflLibraryInitEx);
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
			Alloc = GETPROCADDRESS(hLibgfl, gflMemoryAlloc);
			Realloc = GETPROCADDRESS(hLibgfl, gflMemoryRealloc);
			Free = GETPROCADDRESS(hLibgfl, gflMemoryFree);
#undef GETPROCADDRESS
		}
	}
	~GflLibrary() noexcept
	{
		_CrtDumpMemoryLeaks();
		if (hLibgfl)
			::FreeLibrary(hLibgfl);
	}
	bool isLoaded() const  noexcept
	{
		return hLibgfl != nullptr;
	}
	decltype(::gflLibraryInit) *LibraryInit = nullptr;
	decltype(::gflLibraryInitEx) *LibraryInitEx = nullptr;
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
	decltype(::gflMemoryAlloc) *Alloc = nullptr;
	decltype(::gflMemoryRealloc) *Realloc = nullptr;
	decltype(::gflMemoryFree) *Free = nullptr;
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
		OutputDebugStr("[%08X] GflLibraryInit: %p\r\n", ::GetCurrentThreadId(), this);

		if (lib.isLoaded())
		{
			//auto result = lib.LibraryInit();
			auto result = lib.LibraryInitEx(allocCallBack, reallocCallBack, freeCallback, this);
			GlfCheckError(result);
			if (enableLzw)
				lib.EnableLZW(GFL_TRUE);
		}
	}
	~GflLibraryInit()
	{
		OutputDebugStr("[%08X] ~GflLibraryInit: %p\r\n", ::GetCurrentThreadId(), this);

		if (lib.isLoaded())
			lib.LibraryExit();
	}
	class LargeHeapManager
	{
	public:
		CRITICAL_SECTION cs;
		LargeHeapManager()
		{
			::InitializeCriticalSection(&cs);
		};
		~LargeHeapManager()
		{
			::DeleteCriticalSection(&cs);
		}

		std::map<void*, std::unique_ptr<void, decltype(&::LocalFree)>> listOfHeap;
	};

	static LargeHeapManager* GetHeapManager()
	{
		static LargeHeapManager instance;
		return &instance;
	}

	HLOCAL DettachFromHeapManager(void* ptr)
	{
		CriticalSectionScope cs(&GetHeapManager()->cs);
		auto &listOfHeap = GetHeapManager()->listOfHeap;
		auto itr = listOfHeap.find(ptr);
		if (itr != listOfHeap.end())
		{
			auto hLocal = itr->second.release();
			OutputDebugStr("[%08X] Dettach: %p\r\n", ::GetCurrentThreadId(), ptr);
			return hLocal;
		}
		return nullptr;
	}

private:

	struct CriticalSectionScope
	{
		CRITICAL_SECTION *cs;
		CriticalSectionScope(CRITICAL_SECTION *cs) : cs(cs)
		{
			::EnterCriticalSection(cs);
		}
		~CriticalSectionScope()
		{
			::LeaveCriticalSection(cs);
		}
	};

	const static size_t HeapThreathold = 1 * 1024 * 1024;
	static void* GFLAPI allocCallBack(size_t size, void* user_parms)
	{
		if (size > HeapThreathold)
		{
			OutputDebugStr("[%08X] Custom Allocator: %u Bytes ", ::GetCurrentThreadId(), size);
			auto this_ = reinterpret_cast<GflLibraryInit*>(user_parms);
			CriticalSectionScope cs(&this_->GetHeapManager()->cs);
			auto &listOfHeap = this_->GetHeapManager()->listOfHeap;

#ifdef NDEBUG
			size += 16;
#endif
			auto hLocal = ::LocalAlloc(LMEM_MOVEABLE, size);
			if (hLocal)
			{
				auto p = ::LocalLock(hLocal);
				listOfHeap.emplace(
					std::piecewise_construct,
					std::forward_as_tuple(p),
					std::forward_as_tuple(hLocal, &::LocalFree));
				OutputDebugStr("->Allocates: %p \r\n", p);
				return p;
			}
			}
#ifndef NDEBUG
		return malloc(size);
#else
		return malloc(size + 16);
#endif
		}
	static void* GFLAPI reallocCallBack(void* ptr, size_t new_size, void* user_parms)
	{
		auto this_ = reinterpret_cast<GflLibraryInit*>(user_parms);
		CriticalSectionScope cs(&this_->GetHeapManager()->cs);
		auto &listOfHeap = this_->GetHeapManager()->listOfHeap;
		auto itr = listOfHeap.find(ptr);
		if (itr != listOfHeap.end())
		{
			HLOCAL hNewLoacl = ::LocalReAlloc(itr->second.get(), new_size, LMEM_MOVEABLE);
			if (!hNewLoacl)
				return nullptr;

			itr->second.release();
			listOfHeap.erase(itr);

			auto p = ::LocalLock(hNewLoacl);
			listOfHeap.emplace(
				std::piecewise_construct,
				std::forward_as_tuple(p),
				std::forward_as_tuple(hNewLoacl, &::LocalFree));
			return p;
		}
		return realloc(ptr, new_size);
	}
	static void GFLAPI freeCallback(void* ptr, void* user_parms)
	{
		auto this_ = reinterpret_cast<GflLibraryInit*>(user_parms);
		CriticalSectionScope cs(&this_->GetHeapManager()->cs);
		auto &listOfHeap = this_->GetHeapManager()->listOfHeap;
		if (listOfHeap.size() > 0 && listOfHeap.count(ptr) > 0)
		{
			OutputDebugStr("[%08X] Custom Deleter: %p\r\n", ::GetCurrentThreadId(), ptr);
			auto itr = listOfHeap.find(ptr);
			if (itr != listOfHeap.end())
			{
				if (itr->second)
				{
					OutputDebugStr("->LocalFree: %p\r\n", itr->second.get());
					assert(::LocalFree(itr->second.release()) == NULL);
				}
				else
				{
					//nothing
					OutputDebugStr("->Already Deleted: %p\r\n", ptr);
				}

				listOfHeap.erase(itr);
				return;
			}
		}
		return free(ptr);
	}
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
	void Free()
	{
		if (!hadFree)
		{
			lib.FreeFileInformation(this);
			hadFree = true;
		}
	}
	~GflInfomation()
	{
		Free();
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