#include "stdafx.h"

#include "susie.hpp"
#include <cstdlib>
#include <cstring>
#include "gfl.hpp"
#include <cassert>

#if _DEBUG
int main()
{
	HLOCAL hBm = {};
	HLOCAL hBInfo = {};
	SUSIE_PICTUREINFO pi;
	assert(SUSIE_RESULT::ALL_RIGHT == GetPictureInfo("test.psd", 0, SUSIE_FLAG::SPI_INPUT_FILE, &pi));
	assert(SUSIE_RESULT::ALL_RIGHT == GetPicture("test.psd", 0, SUSIE_FLAG::SPI_INPUT_FILE, &hBInfo, &hBm, nullptr, 0));
}
#endif
