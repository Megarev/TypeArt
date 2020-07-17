#include "MenuState.h"

#ifdef _WIN32
void MenuState::LoadFileImage() {
	std::wstring filepath = ImageLoader::Get().LoadFile();
	if (filepath != L"") {
		LevelManager::Get().SetLevelLoaded(filepath);
		LevelManager::Get().SetIsLevelLoaded(true);
		SetState(State::Play);
	}
}

void MenuState::Load_File_Image() {
	// Linux method
}
#endif

#ifdef __linux__
void MenuState::Load_File_Image() {
	std::string filepath = ImageLoader::Get().Load_File();
	if (filepath != "") {
		LevelManager::Get().SetLevelLoaded(filepath);
		LevelManager::Get().SetIsLevelLoaded(true);
		SetState(State::Play);
	}
}

void MenuState::LoadFileImage() { 
	// Windows method 
}
#endif

MenuState::MenuState(olc::PixelGameEngine* p)
	: GameState(p) {

	LevelManager::Get().SetIsLevelLoaded(false);
	index = 0;

	pos = { 0, 8 + 8 * index };
}

void MenuState::Move(int direction) {

	int n = nLevels;

	switch (direction) {
	case 1: //Down
		index++;
		if (index > n - 1) index = n - 1;
		pos = { 0, 10 + 8 * index };
		break;
	case -1: //Up
		index--;
		if (index < 0) index = 0;
		pos = { 0, 10 + 8 * index };
		break;
	}
}

void MenuState::Input() {
	int cursorDir = (pge->GetKey(olc::DOWN).bPressed - pge->GetKey(olc::UP).bPressed);
	Move(std::move(cursorDir));

	if (pge->GetKey(olc::Z).bPressed) {
		SetState(Settings);
	}
}

void MenuState::Logic(float dt) {
	//If player has selected a level, enter play state
	if (pge->GetKey(olc::ENTER).bPressed || pge->GetKey(olc::SPACE).bPressed) {
		if (LevelManager::Get().GetPlayableLevelState(index)) {
			LevelManager::Get().SetLevel(index);
			SetState(Play);
		}
	}
	else if (pge->GetKey(olc::SHIFT).bHeld && pge->GetKey(olc::O).bPressed) {
		// If player has loaded a level
		switch (ImageLoader::Get().type) {
		case 1: // Windows
			LoadFileImage();
			break;
		case 2: // Linux
			Load_File_Image();
			break;
		}
	}
}

void MenuState::Render() {
	auto [x, y] = pos;

	//Draw Selection cursor
	pge->FillTriangle(x, y, x + 4, y + 4, x, y + 8);
	pge->DrawString(x + 12, 0, "Level Select");
	pge->DrawLine(0, 8, pge->ScreenWidth(), 8);
	int n = nLevels;

	for (int i = 0; i < n; i++) {

		std::string name = GetName(i);

		int posX = x + (i == index) ? 15 : 10;
		int posY = 10 + 8 * i;

		olc::Pixel color = (i == index) ? olc::CYAN : olc::BLUE;
		if (!LevelManager::Get().GetPlayableLevelState(i)) color = olc::GREY;
		pge->DrawString(posX, posY, std::move(name), color);
	}
}

std::string MenuState::GetName(int n) {
	if (n > nLevels - 1) n = nLevels - 1;
	return names[n];
}