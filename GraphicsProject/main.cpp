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

		SetGameState<StartState>();

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
			case GameState::Settings:
				SetGameState<SettingsState>();
				break;
			case GameState::Start:
				SetGameState<StartState>();
				break;
			case GameState::Editor:
				SetGameState<EditorState>();
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

	~GameMain() {
		LevelManager::Get().Clear();
	}
};

int main() {

	srand((unsigned)time(0));

	GameMain game;
	if (game.Construct(129, 145, 4, 4)) {
		game.Start();
	}

	return 0;
}