#include "LevelArt.h"

LevelArt::LevelArt() {}

void LevelArt::Initialize(int type) {

    //switch (type) {
    //case Ball:
    //    //backSprite = new olc::Sprite("files/images/ball.png");
    //    break;
    //case MoonLight:
    //    //backSprite = new olc::Sprite("files/images/light.png");
    //    break;
    //case FlatHill:
    //    //backSprite = new olc::Sprite("files/images/flat_hill.png");
    //    break;
    //case SimpleRoom:
    //    //backSprite = new olc::Sprite("files/images/Simple Room.png");
    //    break;
    //}

    backSprite = SpriteFromArray(32, 32, LevelManager::Get().GetSprite(type));
}

void LevelArt::Initialize(const std::string& filepath) {
    backSprite = new olc::Sprite(filepath);
}

void LevelArt::Initialize(const std::wstring& filepath) {
    backSprite = new olc::Sprite(std::string(filepath.begin(), filepath.end()));
}

void LevelArt::Initialize(olc::Pixel* pixels) {
    backSprite = SpriteFromArray(32, 32, pixels);
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