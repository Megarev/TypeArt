#pragma once
#include "../libs/olcPixelGameEngine.h"
#include "LevelArt.h"

class Menu {
private:
	int index; //Selected index
	olc::vi2d pos; //Position of selection cursor

	int nLevels;

	std::string names[3] = { //Level names
		"Ball",
		"Moonlight",
		"Flathill"
	};

	std::vector<bool> playableLevels;
public:
	Menu();
	void Initialize(const olc::vi2d& p);
	void Move(int direction);

	void SetIndex(int value);
	void SetPosition(const olc::vi2d& p);

	void OnKeyPress(LevelArt&);

	void SetPlayableLevelState(int index, bool state);

	int GetIndex() const;
	olc::vi2d GetPos() const;

	std::string GetName(int n) const;
	int GetNLevels() const;

	bool GetPlayableLevelState(int index) const;
};