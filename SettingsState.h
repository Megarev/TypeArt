#pragma once
#include "GameState.h"
#include "GameSettings.h"

class SettingsState : public GameState {
private:
	int index;

	static const int n = 3;
	
	const std::string states[n] = {
		" Easy ", "Medium", " Hard "
	};
public:
	SettingsState(olc::PixelGameEngine* p);

	void Move(int direction);

	void Input() override;
	void Logic(float dt) override;
	void Render() override;
};