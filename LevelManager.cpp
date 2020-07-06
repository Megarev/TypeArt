#include "LevelManager.h"

LevelManager::LevelManager() {
	nLevels = 3;
	//LoadLevelFromFile("data.txt");

	//isInSaveLevels = false;
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

//std::vector<std::string> LevelManager::GetImages() const {
//	return loadedLevels;
//}
//
//std::string LevelManager::GetImageName(int index) {
//	std::string name;
//	std::string imageDir = loadedLevels[index];
//	for (int i = (int)imageDir.size() - 5; i > 0; i--) {
//		if (imageDir[i] == '/') break;
//		name.push_back(imageDir[i]);
//	}
//	std::reverse(name.begin(), name.end());
//
//	return name;
//}
//
//void LevelManager::SaveLevelToFile(const std::string& filepath) {
//	std::ofstream writer(filepath);
//
//	if (writer.is_open()) {
//
//		std::cout << "File Opened" << std::endl;
//
//		for (auto& str : loadedLevels) {
//			writer << str << "\n";
//		}
//
//		writer.close();
//	}
//	else {
//		std::cout << "File not opened" << std::endl;
//	}
//}
//
//void LevelManager::LoadLevelFromFile(const std::string& filepath) {
//	std::ifstream reader(filepath);
//
//	if (reader.is_open()) {
//		std::string line;
//		while (std::getline(reader, line)) {
//			loadedLevels.push_back(line);
//		}
//
//		reader.close();
//	}
//	else {
//		std::cout << "File not opened" << std::endl;
//	}
//}
//
//void LevelManager::LoadLevel(const std::string& str) {
//	loadedLevels.push_back(str);
//}
//
//std::string LevelManager::GetImageFilePath() const {
//	return loadedLevels[selectedLevel];
//}
//
//void LevelManager::SetIsLevelLoaded(bool state) {
//	isLevelLoaded = state;
//}
//
//bool LevelManager::GetIsLevelLoaded() const {
//	return isLevelLoaded;
//}
//
//void LevelManager::SetIsInSaveLevels(bool state) {
//	isInSaveLevels = state;
//}
//
//bool LevelManager::GetIsInSaveLevels() const {
//	return isInSaveLevels;
//}