#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class LevelManager {
private:
	LevelManager();

	int nLevels; //Preloaded levels

	std::vector<bool> playableLevels;
	std::vector<std::string> loadedLevels;
	int selectedLevel;
	bool isInSaveLevels, isLevelLoaded; //Is a level loaded using image loader
public:
	static LevelManager& Get() {
		static LevelManager levelManager;
		return levelManager;
	}

	void Initialize();

	void SetPlayableLevelState(int index, bool state);
	bool GetPlayableLevelState(int index) const;
	
	void SetNextLevelState(bool state);

	void SetLevel(int n);
	int GetSelectedLevel() const;
	int GetNLevels() const;

	void LoadLevel(const std::string& str);
	std::string GetImageFilePath() const;

	std::vector<std::string> GetImages() const;
	std::string GetImageName(int index);

	void SaveLevelToFile(const std::string& filepath);
	void LoadLevelFromFile(const std::string& filepath);
	
	void SetIsLevelLoaded(bool state);
	bool GetIsLevelLoaded() const;

	void SetIsInSaveLevels(bool state);
	bool GetIsInSaveLevels() const;
};