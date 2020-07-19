#pragma once
#include "GameState.h"
#include "GameSettings.h"

class SettingsState : public GameState {
private:
	int index, textTypeIndex; //Index is the difficulty selected

	static const int n = 3;
	static const int nTypes = 3;
	
	const std::string states[n] = {
		" Easy ", "Medium", " Hard "
	};

	const std::string textTypes[nTypes] = {
		"Arrow Keys", "WASD Keys ", "Both Types"
	};
public:
	SettingsState(olc::PixelGameEngine* p);

	void Move(int direction);
	void TextTypeSelect(int dir);

	void Input() override;
	void Logic(float dt) override;
	void Render() override;
};