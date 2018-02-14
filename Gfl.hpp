#pragma once
#include "libgfl.h"
#include <vector>
#include <memory>
#include <cassert>

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

class GflFormats
{
private:
	template <class Predicate>
	static std::vector<GFL_FORMAT_INFORMATION> getFormats(Predicate pred)
	{
		auto n = ::gflGetNumberOfFormat();
		std::vector<GFL_FORMAT_INFORMATION> formats(n);
		for (auto i = 0; i < n; i++)
		{
			if (pred(i))
			{
				GFL_FORMAT_INFORMATION info;
				auto result = ::gflGetFormatInformationByIndex(i, &info);
				GlfCheckError(result);
				formats.emplace_back(info);
			}
		}
		return formats;

	}
public:
	static std::vector<GFL_FORMAT_INFORMATION> getAllFormats()
	{
		return getFormats([](auto) { return true; });
	}
	static std::vector<GFL_FORMAT_INFORMATION> getReadableFormats()
	{
		return getFormats([](auto i) { return ::gflFormatIsReadableByIndex(i); });
	}
};

class GflLibraryInit final
{
public:
	GflLibraryInit(bool enableLzw = true)
	{
		auto result = ::gflLibraryInit();
		GlfCheckError(result);
		if (enableLzw)
			::gflEnableLZW(GFL_TRUE);
	}
	~GflLibraryInit()
	{
		::gflLibraryExit();
	}
};

class GflInfomation final : public GFL_FILE_INFORMATION
{
private:
	bool hadFree = false;
public:
	GflInfomation() : GFL_FILE_INFORMATION() {}
	GflInfomation(GflInfomation && other) : GFL_FILE_INFORMATION(other)
	{
		std::swap(hadFree, other.hadFree);
	}
	void free()
	{
		if (!hadFree)
		{
			::gflFreeFileInformation(this);
			hadFree = true;
		}

	}
	~GflInfomation()
	{
		if (!hadFree)
			::gflFreeFileInformation(this);
	}
};

struct GflBitmapDeleter
{
	void operator()(GFL_BITMAP* ptr) {
		::gflFreeBitmap(ptr);
	}
};

typedef std::unique_ptr<GFL_BITMAP, GflBitmapDeleter> GflBitmapPtr;

inline GflBitmapPtr GflMakeBitmapPtr(GFL_BITMAP *ptr)
{
	return GflBitmapPtr(ptr);
}

class GflBitmap final
{
private:
	GflBitmapPtr ptr;
public:
	GflBitmap(GFL_BITMAP *_ptr = nullptr) : ptr(_ptr)
	{
	}
	template <class _D>
	GflBitmap(std::unique_ptr<GFL_BITMAP, _D> &&_ptr) : ptr(_ptr)
	{
	}
};

class GflLoadParam final : public GFL_LOAD_PARAMS
{
public:
	GflLoadParam()
	{
		gflGetDefaultLoadParams(this);
	}
};