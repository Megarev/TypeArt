#pragma once
#include "../libs/olcPixelGameEngine.h"
#include <deque>

enum Direction {
	Up = 49, Down = 50, Left = 51, Right = 52
};

class LevelGenerator {
private:
	std::deque<uint8_t> directions;
	olc::vf2d textPos;

	int score;
public:
	LevelGenerator() {}

	void Generate();

	void Initialize(int n);

	void Logic(const olc::vf2d& pos) {
		MoveDirections();
		SetTextPosition(pos);
		AddScore();
	}

	void MoveDirections();
	void SetTextPosition(const olc::vf2d&);
	void AddScore();
	void MoveText(float);

	std::deque<uint8_t> GetDirections() const;
	uint8_t GetCurrentDirection() const;
	uint8_t GetCurrentDirection(int pos) const;
	int GetScore() const;
	olc::vf2d GetTextPosition() const;
};