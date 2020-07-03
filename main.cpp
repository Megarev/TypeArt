#include "libs.h"

class GameMain : public olc::PixelGameEngine {
private:
	std::unique_ptr<GameState> state;

	template<typename T>
	void SetGameState() {
		state = std::make_unique<T>(this);
	}
public:
	GameMain() {
		sAppName = "Game";
	}

	bool OnUserCreate() override {
		LevelManager::Get().Initialize();
		LevelManager::Get().SetPlayableLevelState(0, true);

		SetGameState<MenuState>();

		return true;
	}

	bool OnUserUpdate(float dt) override {

		if (state->isStateChanged) {
			switch (state->state) {
			case GameState::Menu:
				SetGameState<MenuState>();
				break;
			case GameState::Play:
				SetGameState<PlayState>();
				break;
			}
			state->isStateChanged = false;
		}

		state->Input();
		state->Logic(dt);
		Clear(olc::BLACK);
		state->Render();

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