#pragma once
#include "../libs/olcPixelGameEngine.h"
#include "GameState.h"

class StartState : public GameState {
private:
	olc::Sprite* sprite = nullptr;
	int spriteMoveMax, dir;
	float pos;
public:
	StartState(olc::PixelGameEngine* p);

	void Input() override;
	void Logic(float dt) override;
	void Render() override;
};