#pragma once
#include "../libs/olcPixelGameEngine.h"

class LevelArt {
private:
	olc::Sprite* backSprite = nullptr;
public:
	enum LevelType {
		Ball,
		MoonLight
	};

	LevelArt() {}

	void Initialize(int type);
	olc::Pixel GetPixelInSprite(int x, int y) const;
};