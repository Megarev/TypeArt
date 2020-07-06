#include "ImageLoader.h"

std::string ImageLoader::LoadFile() {
	OPENFILENAMEA ofn;
	char file[256];
	HWND hwnd = GetConsoleWindow();

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = file;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(file);
	ofn.lpstrFilter = "Image File\0*.png";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = file;
	ofn.nMaxFileTitle = strlen(file);
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn)) {
		std::string filepath = ofn.lpstrFile;
		for (auto& a : filepath) {
			if (a == '\\') a = '/';
		}
	
		return filepath;
	}

	return "";
}