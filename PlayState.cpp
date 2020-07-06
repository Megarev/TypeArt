#include "PlayState.h"

void PlayState::SetTile(int x, int y, bool state = false) {
	if (x < 0 || x > (pge->ScreenWidth() / size) || y < 0 || y > (pge->ScreenHeight() / size - 3)) return;
	positions[y * (pge->ScreenWidth() / size) + x] = state;
}

PlayState::PlayState(olc::PixelGameEngine* p) 
	: GameState(p) {

	player.pos = { 0, 0 };
	size = 4;
	speed = 30.0f;
	positions.clear();

	for (int i = 0; i < (pge->ScreenWidth() / size) * (int)(pge->ScreenHeight() / size - 4); i++) { positions.push_back(0); }
	positions[0] = true;

	level.Initialize((int)(positions.size() / (player.nSize * player.nSize)));

	level.SetTextPosition({ 0.0f, pge->ScreenHeight() - (3.0f * size + 4.0f) });

	//If file is opened by file explorer
	//if (LevelManager::Get().GetIsLevelLoaded()) {
	//	levelArt.Initialize(LevelManager::Get().GetImageFilePath());
	//}
	//else {
	//	//If level is opened from the saved Levels menu
	//	if (LevelManager::Get().GetIsInSaveLevels()) {
	//		levelArt.Initialize(LevelManager::Get().GetImageFilePath());
	//	}
	//	else {
	//		//Open level from main menu
	//		levelArt.Initialize(LevelManager::Get().GetSelectedLevel());
	//	}
	//}

	levelArt.Initialize(LevelManager::Get().GetSelectedLevel());

	for (int i = 0; i < player.nSize; i++) {
		for (int j = 0; j < player.nSize; j++) {
			SetTile(player.pos.x / size + j, player.pos.y / size + i, true);
		}
	}
}

void PlayState::Input() {
	if (pge->GetKey(olc::ESCAPE).bPressed) {
		SetState(Menu);
	}

	const olc::Key& dir = (olc::Key)level.GetCurrentDirection();

	if (pge->GetKey(dir).bPressed) {
		level.Logic({ level.GetTextPosition().x - 10.0f, level.GetTextPosition().y });

		player.Move(pge->ScreenWidth(), pge->ScreenHeight(), 2 * size);

		//Show the pixels at the position of player
		for (int i = 0; i < player.nSize; i++) {
			for (int j = 0; j < player.nSize; j++) {
				SetTile(player.pos.x / size + j, player.pos.y / size + i, true);
			}
		}

		if (level.GetDirections().size() == 0) {
			LevelManager::Get().SetNextLevelState(true);
			//if (!LevelManager::Get().GetIsLevelLoaded()) {}
			SetState(Menu);
		}
	}
	speed += (pge->GetKey(olc::W).bPressed - pge->GetKey(olc::S).bPressed);
}

void PlayState::Logic(float dt) {
	dt = std::fminf(dt, 2.0f);

	level.MoveText(speed * dt);

	if (level.GetTextPosition().x > pge->ScreenWidth()) {
		SetState(Menu);
	}
}

void PlayState::Render() {
	//Draw the front sprite
	pge->DrawSprite(0, 0, levelArt.GetSprite(), size);

	for (int i = 0; i < pge->ScreenHeight() / size - 4; i++) {
		for (int j = 0; j < pge->ScreenWidth() / size; j++) {
			if (positions[i * (pge->ScreenWidth() / size) + j]) continue;

			pge->FillRect(j * size, i * size, size, size, olc::BLACK);
		}
	}

	//Draw player
	pge->FillRect(player.pos.x, player.pos.y, 2 * size, 2 * size, olc::MAGENTA);

	//Draw the level
	for (int i = 0; i < (int)level.GetDirections().size(); i++) {
		const int& dir = level.GetCurrentDirection(i);

		olc::Pixel color = olc::WHITE;

		auto [x, y] = (olc::vi2d)level.GetTextPosition();
		int distance = 10;

		std::string str;

		switch (dir) {
		case Right: str = ">"; break;
		case Down:  str = "V"; break;
		case Left:  str = "<"; break;
		case Up:    str = "^"; break;
		}

		pge->DrawString(x - i * distance, y, std::move(str), color);
	}

	//Draw line and score
	pge->DrawLine(0, pge->ScreenHeight() - (4 * size + 1), pge->ScreenWidth(), pge->ScreenHeight() - (4 * size + 1), olc::Pixel(200, 200, 200));
	pge->DrawString(0, pge->ScreenHeight() - (3 * size - 3), "Score: " + std::to_string(level.GetScore()), olc::DARK_CYAN);
}