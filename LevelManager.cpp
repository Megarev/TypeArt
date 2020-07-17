#include "LevelManager.h"

LevelManager::LevelManager() {
	//nLevels = 3;
	nLevels = 4;
}

void LevelManager::Initialize() {
	playableLevels.resize(nLevels);
	//playableLevels[0] = true;

	for (int i = 0; i < nLevels; i++) {
		SetPlayableLevelState(i, true);
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