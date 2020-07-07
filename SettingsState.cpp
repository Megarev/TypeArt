#include "SettingsState.h"

float speedEasy = 15.0f;
float speedMedium = 30.0f;
float speedHard = 45.0f;

float speed = speedMedium;

SettingsState::SettingsState(olc::PixelGameEngine* p)
	: GameState(p) {
	index = 0;
}

void SettingsState::Move(int direction) {
	switch (direction) {
	case 1:
		index++;
		if (index > (n - 1)) index = n - 1;
		break;
	case -1:
		index--;
		if (index < 0) index = 0;
		break;
	}
}

void SettingsState::Input() {
	int direction = (pge->GetKey(olc::DOWN).bPressed - pge->GetKey(olc::UP).bPressed);
	Move(std::move(direction));

	if (pge->GetKey(olc::ENTER).bPressed) {
		SetState(Menu);
	}
}

void SettingsState::Logic(float dt) {
	switch (index) {
	case 0:
		speed = speedEasy;
		break;
	case 1:
		speed = speedMedium;
		break;
	case 2:
		speed = speedHard;
		break;
	}
}

void SettingsState::Render() {
	pge->DrawString(30, 0, "Settings");
	pge->DrawLine(0, 8, pge->ScreenWidth(), 8);
	pge->DrawString(10, 16, "Difficulty:");
	
	if (index > 0) pge->FillTriangle(46, 28, 62, 28, 54, 24);
	if (index < n - 1) pge->FillTriangle(46, 42, 62, 42, 54, 46);
	
	olc::Pixel color;
	switch (index) {
	case 0: color = olc::GREEN; break;
	case 1: color = olc::BLUE;  break;
	case 2: color = olc::RED;   break;
	}
	pge->DrawString(32, 32, states[index], color);
}