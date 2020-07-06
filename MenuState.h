#pragma once
#include "GameState.h"
#include "LevelArt.h"
#include "LevelManager.h"
#include "ImageLoader.h"
#include <optional>

class MenuState : public GameState {
private:
	int index; //Selected index
	olc::vi2d pos; //Position of selection cursor

	enum Menu {
		MainLevels = 1,
		SavedLevels = -1
	} menuState;

	int nLevels;

	std::string names[3] = { //Level names
		"Ball",
		"Moonlight",
		"Flathill"
	};
public:
	MenuState(olc::PixelGameEngine* p);

	void Move(int);

	void Input() override;
	void Logic(float) override;
	void Render() override;

	std::string GetName(int n);
};