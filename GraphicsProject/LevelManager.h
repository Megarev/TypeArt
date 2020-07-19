#pragma once
#include <vector>
#include <string>
#include "olcPixelGameEngine.h"

class LevelManager {
private:
	LevelManager();
	olc::Sprite* backSprite = nullptr;

	int nLevels; //Preloaded levels

	std::vector<bool> playableLevels;
	std::vector<std::string> loadedLevels;
	std::vector<std::pair<std::string, std::string>> levels; // Saved levels
	std::vector<olc::Pixel*> sprites; // Saved sprites

	int selectedLevel;
	bool isLevelLoaded; //Is a level loaded using image loader
public:
	static LevelManager& Get() {
		static LevelManager levelManager;
		return levelManager;
	}

	void Initialize();

	void Clear();

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

	std::string GetName(int n) const;
	std::string GetDir(int n) const;

	olc::Pixel* GetSprite(int n) const;
};