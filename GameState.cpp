#include "GameState.h"

GameState::GameState(olc::PixelGameEngine* p)
	: pge(p) {
	isStateChanged = false;
	isFileLoaded = false;
}

void GameState::SetState(State newState) {
	state = newState;
	isStateChanged = true;
}

void GameState::SetIsFileLoaded(bool state) {
	isFileLoaded = state;
}