#include "Menu.h"

Menu::Menu() {
	nLevels = 3;

	playableLevels.resize((int)nLevels);
	playableLevels[0] = true;
}

void Menu::Initialize(const olc::vi2d& p) {
	pos = p;
	index = 0;
}

void Menu::Move(int direction) {
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

void Menu::SetIndex(int value) {
	index = value;
}

void Menu::SetPosition(const olc::vi2d& p) {
	pos = p;
}

void Menu::OnKeyPress(LevelArt& art) {
	art.Initialize(index);
}

void Menu::SetPlayableLevelState(int index, bool state) {
	playableLevels[index] = state;
}

int Menu::GetIndex() const {
	return index;
}

olc::vi2d Menu::GetPos() const {
	return pos;
}

std::string Menu::GetName(int n) const {
	n = (int)std::fminf(n, nLevels);
	return names[n];
}

int Menu::GetNLevels() const {
	return nLevels;
}

bool Menu::GetPlayableLevelState(int index) const {
	if (index < (int)playableLevels.size()) {
		return playableLevels[index];
	}
}