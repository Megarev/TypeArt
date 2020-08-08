#pragma once
#include "GameState.h"
#include "Slider.h"
#include "olcPGEX_AdditionalColours.h"
#include "LevelManager.h"

class EditorState : public GameState {
private:
	bool isGridShown;
	int size;
	olc::Sprite* sprite = nullptr;
	Slider HSVSlider[3];
public:
	EditorState(olc::PixelGameEngine* p);
	~EditorState();
	void Input() override;
	void Logic(float dt) override;
	void Render() override;
	
	void DrawGrid(int x1, int y1, int x2, int y2, int distance, olc::Pixel color = olc::WHITE);
};