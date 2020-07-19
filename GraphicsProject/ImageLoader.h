#pragma once
#include "../libs/olcPixelGameEngine.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

class ImageLoader {
private:
	ImageLoader();
public:
	static ImageLoader& Get() {
		static ImageLoader imageLoader;
		return imageLoader;
	}

	uint8_t type; // Operating System
	/*
		type == 1 => Windows
		type == 2 => Linux
	*/

	std::wstring LoadFile(); // For Windows
	std::string Load_File();  // For Linux
};