#pragma once
#include "../libs/olcPixelGameEngine.h"

class GameState {
public:
	enum State {
		Menu,
		Play
	} state;
	bool isStateChanged;

	olc::PixelGameEngine* pge;

	GameState(olc::PixelGameEngine* p);

	void SetState(State newState);

	virtual void Input() {}
	virtual void Logic(float) = 0;
	virtual void Render() {}
};