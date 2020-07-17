#include "StartState.h"

StartState::StartState(olc::PixelGameEngine* p)
	: GameState(p) {
	sprite = new olc::Sprite("files/images/Logo.png");
	spriteMoveMax = 2;
	pos = (float)pge->ScreenHeight() / 2 - spriteMoveMax;
	dir = 1;
}

void StartState::Input() {
	if (pge->GetKey(olc::ENTER).bPressed) {
		SetState(Menu);
	}
}

void StartState::Logic(float dt) {
	if (pos < pge->ScreenHeight() / 2 - spriteMoveMax) dir = 1;
	else if (pos > pge->ScreenHeight() / 2 + spriteMoveMax) dir = -1;
	
	pos += 5 * dir * dt;
}

void StartState::Render() {
	pge->DrawSprite((pge->ScreenWidth() - sprite->width) / 2, (int)pos, sprite);
	pge->DrawString((int)(pge->ScreenWidth() - 1.5f * sprite->width), pge->ScreenHeight() / 2 + spriteMoveMax + 15, "Press Enter");
}