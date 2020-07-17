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
	bool isLevelLoaded; //Is a level loaded using image loader
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

	bool GetIsLevelLoaded() const;
	void SetIsLevelLoaded(bool state);

	void SetLevelLoaded(const std::string& filepath);
	void SetLevelLoaded(const std::wstring& filepath);
	std::string GetLevelLoaded() const;
};