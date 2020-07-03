#include "MenuState.h"

MenuState::MenuState(olc::PixelGameEngine* p)
	: GameState(p) {
	nLevels = 3;
	index = 0;
}

void MenuState::Move(int direction) {
	switch (direction) {
	case 1: //Down
		index++;
		index = (int)std::fminf(index, nLevels - 1);
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
}

void MenuState::Logic(float dt) {
	//If player has selected a level, enter play state
	if (pge->GetKey(olc::ENTER).bPressed || pge->GetKey(olc::SPACE).bPressed) {
		if (LevelManager::Get().GetPlayableLevelState(index)) {
			LevelManager::Get().SetLevel(index);
			SetState(Play);
		}
	}
}

void MenuState::Render() {
	auto [x, y] = pos;

	//Draw Selection cursor
	pge->FillTriangle(x, y, x + 4, y + 4, x, y + 8);

	for (int i = 0; i < nLevels; i++) {

		int posX = x + (i == index) ? 15 : 10;
		int posY = 8 * i;

		olc::Pixel color;
		if (!LevelManager::Get().GetPlayableLevelState(i)) color = olc::GREY;
		else {
			color = (i == index) ? olc::CYAN : olc::BLUE;
		}
		pge->DrawString(posX, posY, GetName(i), color);
	}
}

std::string MenuState::GetName(int n) {
	n = (int)std::fminf(n, nLevels);
	return names[n];
}