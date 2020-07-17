#include "ImageLoader.h"

#ifdef _WIN32
ImageLoader::ImageLoader() {
	type = 1;
}

std::wstring ImageLoader::LoadFile() {
	OPENFILENAME ofn;
	wchar_t file[256];
	HWND hwnd = NULL;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = file;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(file);
	ofn.lpstrFilter = L"Image File\0*.png";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = file;
	ofn.nMaxFileTitle = lstrlenW(file);
	ofn.lpstrInitialDir = L"files\\images";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn)) {
		std::wstring filepath = ofn.lpstrFile;
		return filepath;
	}

	return L"";
}
#endif

#ifdef __linux__
ImageLoader::ImageLoader() {
	type = 2;
}

std::string ImageLoader::Load_File() {
	char filename[1024];
	FILE* f = popen("zenity --file-selection", "r");
	fgets(filename, 1024, f);

	return filename;
}
#endif