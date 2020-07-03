#include "GameState.h"

GameState::GameState(olc::PixelGameEngine* p)
	: pge(p) {
	isStateChanged = false;
}

void GameState::SetState(State newState) {
	state = newState;
	isStateChanged = true;
}