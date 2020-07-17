#pragma once
#include "GameState.h"
#include "LevelArt.h"
#include "LevelManager.h"
#include "GameSettings.h"
#include "ImageLoader.h"

class MenuState : public GameState {
private:
	int index; //Selected index
	olc::vi2d pos; //Position of selection cursor

	static const int nLevels = 4;

	std::string names[nLevels] = { //Level names
		"Ball",
		"Moonlight",
		"Flathill",
		"SimpleRoom"
	};
public:
	MenuState(olc::PixelGameEngine* p);

	void Move(int);

	void Input() override;
	void Logic(float) override;
	void Render() override;

	void LoadFileImage();   // Windows
	void Load_File_Image(); // Linux

	std::string GetName(int n);
};