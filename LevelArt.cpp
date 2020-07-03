#include "LevelArt.h"

LevelArt::LevelArt() {}

void LevelArt::Initialize(int type) {
    switch (type) {
    case Ball:
        backSprite = new olc::Sprite("files/images/ball.png");
        break;
    case MoonLight:
        backSprite = new olc::Sprite("files/images/light.png");
        break;
    case FlatHill:
        backSprite = new olc::Sprite("files/images/flat_hill.png");
        break;
    }
}

olc::Pixel LevelArt::GetPixelInSprite(int x, int y) const {
    return backSprite->GetPixel(x, y);
}

olc::Sprite* LevelArt::GetSprite() const {
    return backSprite;
}

LevelArt::~LevelArt() {
    delete backSprite;
}