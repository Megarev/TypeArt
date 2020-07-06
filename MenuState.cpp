#include "MenuState.h"

MenuState::MenuState(olc::PixelGameEngine* p)
	: GameState(p) {

	menuState = MainLevels;
	nLevels = LevelManager::Get().GetNLevels();
	LevelManager::Get().SetIsLevelLoaded(false);
	index = 0;
}

void MenuState::Move(int direction) {

	int n = (menuState == SavedLevels) ? LevelManager::Get().GetImages().size() : nLevels;

	switch (direction) {
	case 1: //Down
		index++;
		index = (int)std::fminf(index, n - 1);
		pos = { 0, 8 * index };
		break;
	case -1: //Up
		index--;
		index = (int)std::fmaxf(0, index);
		pos = { 0, 8 * index };
		break;
	}
}

void MenuState::Input() {
	int cursorDir = (pge->GetKey(olc::DOWN).bPressed - pge->GetKey(olc::UP).bPressed);
	Move(std::move(cursorDir));

	if (LevelManager::Get().GetImages().size() > 0) {
		if (pge->GetKey(olc::RIGHT).bPressed) menuState = SavedLevels;
		else if (pge->GetKey(olc::LEFT).bPressed) menuState = MainLevels;
	}

	if (pge->GetKey(olc::O).bPressed) {
		
		const std::string& filepath = ImageLoader::Get().LoadFile();

		if (filepath != "") {
			LevelManager::Get().LoadLevel(filepath);
			LevelManager::Get().SetIsLevelLoaded(true);
			SetIsFileLoaded(true);

			SetState(Play);
		}
	}
}

void MenuState::Logic(float dt) {
	//If player has selected a level, enter play state
	if (pge->GetKey(olc::ENTER).bPressed || pge->GetKey(olc::SPACE).bPressed) {
		if (menuState == MainLevels) {
			if (LevelManager::Get().GetPlayableLevelState(index)) {
				LevelManager::Get().SetIsInSaveLevels(false);
				LevelManager::Get().SetLevel(index);
				SetState(Play);
			}
		}
		else {
			LevelManager::Get().SetIsInSaveLevels(true);
			SetState(Play);
		}
	}
}

void MenuState::Render() {
	auto [x, y] = pos;

	//Draw Selection cursor
	pge->FillTriangle(x, y, x + 4, y + 4, x, y + 8);

	int n = (menuState == SavedLevels) ? LevelManager::Get().GetImages().size() : nLevels;

	for (int i = 0; i < n; i++) {

		std::string name = (menuState == SavedLevels) ? LevelManager::Get().GetImageName(i) : GetName(i);

		int posX = x + (i == index) ? 15 : 10;
		int posY = 8 * i;

		olc::Pixel color = (i == index) ? olc::CYAN : olc::BLUE;;
		if (!LevelManager::Get().GetPlayableLevelState(i) && menuState == MainLevels) color = olc::GREY;
		pge->DrawString(posX, posY, name, color);
	}
}

std::string MenuState::GetName(int n) {
	n = (int)std::fminf(n, nLevels);
	return names[n];
}