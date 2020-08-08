#include "LevelManager.h"

LevelManager::LevelManager() {
	levels = {
		{ "Ball",	    "files/images/ball.png" },
		{ "Moonlight",  "files/images/light.png" },
		{ "FlatHill",   "files/images/flat_hill.png" },
		{ "SimpleRoom", "files/images/simple_room.png" }
	};

	nLevels = (int)levels.size();
	isImageMadeInEditor = false;
}

void LevelManager::Initialize() {
	playableLevels.resize(nLevels);
	//playableLevels[0] = true;

	for (int i = 0; i < nLevels; i++) {
		SetPlayableLevelState(i, true);
	}

	for (int i = 0; i < nLevels; i++) {

		sprites.push_back(new olc::Pixel[32 * 32]);

		const std::string& spriteDir = LevelManager::Get().GetDir(i);

		sprites[i] = (new olc::Sprite(spriteDir))->GetData();
	}
}

void LevelManager::SetPlayableLevelState(int index, bool state) {
	if (index >= nLevels) return;
	playableLevels[index] = state;
}

bool LevelManager::GetPlayableLevelState(int index) const {
	return playableLevels[index];
}

void LevelManager::SetNextLevelState(bool state) {
	SetPlayableLevelState(selectedLevel + 1, state);
}

void LevelManager::SetLevel(int n) {
	selectedLevel = n;
}

int LevelManager::GetSelectedLevel() const {
	return selectedLevel;
}

int LevelManager::GetNLevels() const {
	return nLevels;
}

bool LevelManager::GetIsLevelLoaded() const {
	return isLevelLoaded;
}

void LevelManager::SetIsLevelLoaded(bool state) {
	isLevelLoaded = state;
}

void LevelManager::SetLevelLoaded(const std::string& filepath) {
	loadedLevels.push_back(filepath);
}

void LevelManager::SetLevelLoaded(const std::wstring& filepath) {
	loadedLevels.push_back(std::string(filepath.begin(), filepath.end()));
}

std::string LevelManager::GetLevelLoaded() const {
	return loadedLevels.back();
}

std::string LevelManager::GetName(int n) const {
	if (n < nLevels) {
		return levels[n].first;
	}

	return "";
}

std::string LevelManager::GetDir(int n) const {
	if (n < nLevels) {
		return levels[n].second;
	}

	return "";
}

olc::Pixel* LevelManager::GetSprite(int n) const {
	if (n < nLevels) {
		return sprites[n];
	}

	return nullptr;
}

void LevelManager::SaveSprite(olc::Pixel* sprite) {
	sprites.push_back(sprite);
}

std::size_t LevelManager::GetNImages() const {
	return sprites.size();
}

bool& LevelManager::GetisImageMadeInEditor() {
	return isImageMadeInEditor;
}

olc::Pixel* LevelManager::GetBackImage() const {
	return sprites.back();
}

void LevelManager::Clear() {
	for (auto& a : sprites) {
		delete a;
	} sprites.clear();
}