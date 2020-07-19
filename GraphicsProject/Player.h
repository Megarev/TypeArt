#pragma once
#include "../libs/olcPixelGameEngine.h"

struct Player {
	olc::vi2d pos;
	int direction, nSize;

	Player(); 

	void Move(int w, int h, int pixelSize);
};