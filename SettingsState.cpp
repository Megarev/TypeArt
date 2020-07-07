#include "SettingsState.h"

float speedEasy = 15.0f;
float speedMedium = 30.0f;
float speedHard = 45.0f;

float speed = speedMedium;
uint8_t textType = 2;

SettingsState::SettingsState(olc::PixelGameEngine* p)
	: GameState(p) {
	index = 0;
	textTypeIndex = 0;
}

void SettingsState::Move(int direction) {
	switch (direction) {
	case 1:
		index++;
		if (index > n - 1) index = n - 1;
		break;
	case -1:
		index--;
		if (index < 0) index = 0;
		break;
	}
}

void SettingsState::TextTypeSelect(int dir) {
	switch (dir) {
	case 1:
		textTypeIndex++;
		if (textTypeIndex > nTypes - 1) textTypeIndex = nTypes - 1;
		break;
	case -1:
		textTypeIndex--;
		if (textTypeIndex < 0) textTypeIndex = 0;
		break;
	}
}

void SettingsState::Input() {
	Move((pge->GetKey(olc::DOWN).bPressed - pge->GetKey(olc::UP).bPressed));
	TextTypeSelect((pge->GetKey(olc::RIGHT).bPressed - pge->GetKey(olc::LEFT).bPressed));

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

	textType = (uint8_t)textTypeIndex;
}

void SettingsState::Render() {
	pge->DrawString(30, 0, "Settings");
	pge->DrawLine(0, 8, pge->ScreenWidth(), 8);
	
	pge->DrawString(18, 16, "Difficulty:");
	if (index > 0) pge->FillTriangle(52, 28, 68, 28, 60, 24);
	if (index < n - 1) pge->FillTriangle(52, 42, 68, 42, 60, 46);
	
	pge->DrawString(25, 60, "Text Type:");
	if (textTypeIndex > 0) pge->FillTriangle(21, 68, 21, 76, 17, 72);
	if (textTypeIndex < nTypes - 1) pge->FillTriangle(108, 68, 108, 76, 112, 72);

	olc::Pixel color, colorTextType;
	switch (index) {
	case 0: color = olc::GREEN; break;
	case 1: color = olc::BLUE;  break;
	case 2: color = olc::RED;   break;
	}
	
	switch (textTypeIndex) {
	case 0: colorTextType = olc::GREEN; break;
	case 1: colorTextType = olc::BLUE;  break;
	case 2: colorTextType = olc::RED;   break;
	}

	pge->DrawString(35, 32, states[index], color);
	pge->DrawString(25, 72, textTypes[textTypeIndex], colorTextType);
}