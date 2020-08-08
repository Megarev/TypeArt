#pragma once
#include "olcPixelGameEngine.h"

class GameState {
public:
	enum State {
		Start,
		Menu,
		Play,
		Settings,
		Editor
	} state;
	bool isStateChanged;
	//bool isFileLoaded;

	olc::PixelGameEngine* pge;

	GameState(olc::PixelGameEngine* p);

	void SetState(State newState);
	//void SetIsFileLoaded(bool state);

	virtual void Input() {}
	virtual void Logic(float) = 0;
	virtual void Render() {}
};