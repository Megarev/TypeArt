#pragma once
#include "GameState.h"
#include "LevelArt.h"
#include "LevelGenerator.h"
#include "LevelManager.h"
#include "Player.h"

class PlayState : public GameState {
private:
	LevelGenerator level;
	LevelArt levelArt;
	Player player;

	std::vector<bool> positions; //Front sprite cover

	int size;
	float speed;
public:
	PlayState(olc::PixelGameEngine* p);

	void Input() override;
	void Logic(float) override;
	void Render() override;

	void SetTile(int x, int y, bool state);
};
