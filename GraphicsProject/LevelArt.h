#pragma once
#include "olcPixelGameEngine.h"
#include "LevelManager.h"

class LevelArt {
private:
	olc::Sprite* backSprite = nullptr;

	olc::Sprite* SpriteFromArray(int w, int h, olc::Pixel* pixels) {
		olc::Sprite* sprite = new olc::Sprite(w, h);

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				sprite->SetPixel(j, i, pixels[i * w + j]);
			}
		}

		return sprite;
	}
public:
	LevelArt();

	void Initialize(int type);
	void Initialize(const std::string& filepath);
	void Initialize(const std::wstring& filepath);
	void Initialize(olc::Pixel* pixels);
	olc::Pixel GetPixelInSprite(int x, int y) const;
	olc::Sprite* GetSprite() const;

	~LevelArt();
};