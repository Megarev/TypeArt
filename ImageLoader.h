#pragma once
#include "../libs/olcPixelGameEngine.h"
#include <Windows.h>

class ImageLoader {
private:
	ImageLoader() {}
public:
	static ImageLoader& Get() {
		static ImageLoader imageLoader;
		return imageLoader;
	}

	std::string LoadFile();
};