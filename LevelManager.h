#pragma once
#include <vector>

class LevelManager {
private:
	LevelManager() {}

	int nLevels = 3;

	std::vector<bool> playableLevels;
	int selectedLevel;
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
};