#pragma once
#include "../libs/olcPixelGameEngine.h"

class LevelArt {
private:
	olc::Sprite* backSprite = nullptr;
public:
	enum LevelType {
		Ball,
		MoonLight,
		FlatHill,
	};

	LevelArt();

	void Initialize(int type);
	void Initialize(const std::string& filepath);
	olc::Pixel GetPixelInSprite(int x, int y) const;
	olc::Sprite* GetSprite() const;

	~LevelArt();
};