#include "LevelGenerator.h"

void LevelGenerator::Generate() {
	int dir = (rand() % 4) + 49;
	directions.push_back(std::move(dir));
}

void LevelGenerator::Initialize(int n) {
	directions.clear();

	for (int i = 0; i < n; i++) {
		Generate();
	}

	score = 0;
}

void LevelGenerator::MoveDirections() {
	if (directions.size() > 0) {
		directions.pop_front();
	}
}

void LevelGenerator::SetTextPosition(const olc::vf2d& pos) { textPos = pos; }
void LevelGenerator::AddScore() { score++; }
void LevelGenerator::MoveText(float speed) { textPos.x += speed; }

std::deque<uint8_t> LevelGenerator::GetDirections() const { return directions; }
uint8_t LevelGenerator::GetCurrentDirection() const { return directions[0]; }
uint8_t LevelGenerator::GetCurrentDirection(int pos) const { return directions[pos]; }
int LevelGenerator::GetScore() const { return score; }
olc::vf2d LevelGenerator::GetTextPosition() const { return textPos; }