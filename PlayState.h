#pragma once
#include "GameState.h"
#include "LevelArt.h"
#include "LevelGenerator.h"
#include "LevelManager.h"
#include "Player.h"
#include "GameSettings.h"
#include <random>

class PlayState : public GameState {
private:
	LevelGenerator level;
	LevelArt levelArt;
	Player player;

	std::vector<bool> positions; //Front sprite cover
	
	static const int nInputs = 8;
	const olc::Key inputs[nInputs] = {
		olc::LEFT, olc::RIGHT, olc::UP, olc::DOWN,
		olc::W, olc::A, olc::S, olc::D
	};

	bool isChangeState; //Is player has won or the text went right out of bounds
	float accumulator; //if isChangeState is true, then for better transition between states

	olc::vf2d viewMove;
	float viewMoveMax;

	int size;
public:
	PlayState(olc::PixelGameEngine* p);

	float RandomRange(float r1, float r2);

	void Input() override;
	void Logic(float) override;
	void Render() override;

	void SetTile(int x, int y, bool state);
};