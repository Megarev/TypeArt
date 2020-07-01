#pragma once
#include "../libs/olcPixelGameEngine.h"

class LevelArt {
private:
	std::vector<olc::Pixel> pixels;

	void LevelBall();
	void LevelLight();
public:
	enum LevelType {
		Ball,
		MoonLight
	};

	LevelArt() {}

	void Initialize(int type);
	olc::Pixel GetPixel(int x, int y, int w) const;
	void SetPixel(int x, int y, olc::Pixel, int w);

	std::vector<olc::Pixel> GetPixels() const;

};