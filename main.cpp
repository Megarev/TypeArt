#define OLC_PGE_APPLICATION
#include "../libs/olcPixelGameEngine.h"
#include "LevelArt.h"
#include <deque>
#include <ctime>
#include <random>

enum Direction {
	Up = 49, Down = 50, Left = 51, Right = 52
};

class LevelGenerator {
private:
	std::deque<int> directions;
	olc::vf2d textPos;

	int score;
public:
	LevelGenerator() {
		Initialize();
	}

	void Generate() {
		directions.push_back((rand() % 4) + 49);
	}

	void Initialize() {
		for (int i = 0; i < 10; i++) {
			directions.push_back((rand() % 4) + 49);
		}

		score = 1024;
	}

	void SetTextPosition(const olc::vf2d& pos) { textPos = pos; }
	void AddScore() { score++; }
	void MoveText(float speed) { textPos.x += speed; }

	void MoveDirections() {
		if (directions.size() > 0) {
			directions.pop_front();
		}
	}

	std::deque<int> GetDirections() const { return directions; }
	inline int GetCurrentDirection(int pos = 0) const { return directions[pos]; }
	inline int GetScore() const { return score; }
	olc::vf2d GetTextPosition() const { return textPos; }
};

class GameMain : public olc::PixelGameEngine {
private:
	olc::vi2d playerPos;
	int direction;

	LevelGenerator level;
	std::vector<olc::Pixel> levelData;
	LevelArt levelArt;

	int size;
	float speed;
	olc::vf2d viewMove;
	float viewMoveMax;

	float accumulator, delay;

	float RandomRange(float r1, float r2) {
		std::random_device rd;
		std::mt19937 m(rd());
		std::uniform_real_distribution<float> range(r1, r2);

		return range(m);
	}

	void ResetLevel() {
		levelData.clear();

		std::cout << ScreenWidth() << std::endl;
		std::cout << ScreenHeight() << std::endl;

		//for (int i = 0; i < (ScreenWidth() / size) * (ScreenHeight() / size - 3); i++) {
		//	levelData.push_back(olc::BLACK);
		//}

		//levelData[0] = levelArt.GetPixel(0, 0, ScreenWidth() / size);

		levelData = levelArt.GetPixels();

		playerPos = { 0, 0 };
	}
public:
	GameMain() {
		sAppName = "Game";
	}

	bool OnUserCreate() override {

		size = 4;
		speed = 30.0f;

		direction = 1;

		accumulator = 0.0f;
		delay = 0.2f;

		viewMoveMax = 2.0f;

		level.SetTextPosition({ 0.0f, ScreenHeight() - (3.0f * size + 3.0f) });
		levelArt.Initialize(LevelArt::MoonLight);

		ResetLevel();
		playerPos = { 31 * size, 31 * size };

		return true;
	}

	void Input(float dt) {
		const olc::Key& dir = (olc::Key)level.GetCurrentDirection();

		if (GetKey(dir).bPressed) {
			level.MoveDirections();
			level.SetTextPosition({ level.GetTextPosition().x - 10.0f, level.GetTextPosition().y });
			level.AddScore();

			if (level.GetScore() % 10 == 0 && level.GetScore() > 0) {
				viewMove = {
					RandomRange(-viewMoveMax, viewMoveMax),
					RandomRange(-viewMoveMax, viewMoveMax)
				};
			}

			playerPos.x += size * direction;
			if (playerPos.x > ScreenWidth() - size) {
				playerPos.x -= size;
				playerPos.y += size;
				direction = -1;
			}
			else if (playerPos.x < 0) {
				playerPos.x += size;
				playerPos.y += size;
				direction = 1;
			}

			if (playerPos.y > (ScreenHeight() - 4 * size)) {
				playerPos.y -= size;
			}

			levelData[(playerPos.y / size) * (ScreenWidth() / size) + (playerPos.x / size)] = levelArt.GetPixel(playerPos.x / size, playerPos.y / size, ScreenWidth() / size);
		}

		speed += (GetKey(olc::W).bPressed - GetKey(olc::S).bPressed);
	}

	bool OnUserUpdate(float dt) override {

		auto GetPixel = [&](int x, int y) {
			if (x < 0 || x > ScreenWidth() / size || y < 0 || y > ScreenHeight() / size) return olc::BLACK;
			
			return levelData[y * (ScreenWidth() / size) + x];
		};

		//Input
		Input(dt);

		//Logic
		accumulator += dt;
		level.MoveText(speed * dt);

		if (accumulator > delay) {
			accumulator = 0.0f;
			level.Generate();
		}

		if (level.GetTextPosition().x > ScreenWidth()) {
			//Sleep(1000);
			//level.SetTextPosition({ -5.0f * size, level.GetTextPosition().y });
			//level.Initialize();

			//ResetLevel();
		}

		viewMove *= 0.9f;

		//Render
		Clear(olc::BLACK);

		for (int i = 0; i < ScreenHeight() / size - 4; i++) {
			for (int j = 0; j < ScreenWidth() / size; j++) {
				FillRect((int)viewMove.x + j * size, (int)viewMove.y + i * size, size, size, GetPixel(j, i));
			}
		}
		FillRect((int)viewMove.x + playerPos.x, (int)viewMove.y + playerPos.y, size, size, olc::MAGENTA);

		for (int i = 0; i < (int)level.GetDirections().size(); i++) {
			const int& dir = level.GetCurrentDirection(i);

			olc::Pixel color = olc::WHITE;

			auto [x, y] = (olc::vi2d)level.GetTextPosition();
			int distance = 10;

			switch (dir) {
			case Right:
				DrawString((int)viewMove.x + x - i * distance, (int)viewMove.y + y, ">", color);
				break;
			case Down:
				DrawString((int)viewMove.x + x - i * distance, (int)viewMove.y + y, "V", color);
				break;
			case Left:
				DrawString((int)viewMove.x + x - i * distance, (int)viewMove.y + y, "<", color);
				break;
			case Up:
				DrawString((int)viewMove.x + x - i * distance, (int)viewMove.y + y, "^", color);
				break;
			}
		}

		DrawLine((int)viewMove.x, ScreenHeight() - (4 * size + 1), (int)viewMove.x + ScreenWidth(), ScreenHeight() - (4 * size + 1), olc::Pixel(200, 200, 200));
		DrawString((int)viewMove.x, ScreenHeight() - (3 * size - 3), "Score: " + std::to_string(level.GetScore()), olc::DARK_CYAN);

		return true;
	}
};

int main() {

	srand((unsigned)time(0));

	GameMain game;
	if (game.Construct(128, 145, 4, 4)) {
		game.Start();
	}

	return 0;
}