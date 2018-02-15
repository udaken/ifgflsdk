#include "stdafx.h"

#include "susie.hpp"
#include <cstdlib>
#include <cstring>
#include "gfl.hpp"
#include <cassert>

int main()
{
	HLOCAL hBm = {};
	HLOCAL hBInfo = {};
	SUSIE_PICTUREINFO pi;
	assert(SPI_ALL_RIGHT == GetPictureInfo("test.psd", 0, SPI_FLAG::SPI_INPUT_FILE, &pi));
	assert(SPI_ALL_RIGHT == GetPicture("test.psd", 0, SPI_FLAG::SPI_INPUT_FILE, &hBInfo, &hBm, nullptr, 0));
}
