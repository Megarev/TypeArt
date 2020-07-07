#include "LevelManager.h"

LevelManager::LevelManager() {
	nLevels = 3;
}

void LevelManager::Initialize() {
	playableLevels.resize(nLevels);
	playableLevels[0] = true;
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