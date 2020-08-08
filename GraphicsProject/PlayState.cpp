#include "PlayState.h"

void PlayState::SetTile(int x, int y, bool state = false) {
	if (x < 0 || x > (pge->ScreenWidth() / size) || y < 0 || y > (pge->ScreenHeight() / size - 3)) return;
	positions[y * (pge->ScreenWidth() / size) + x] = state;
}

float PlayState::RandomRange(float r1, float r2) {
	std::random_device rd;
	std::mt19937 m(rd());
	std::uniform_real_distribution<float> value(r1, r2);

	return value(m);
}

PlayState::PlayState(olc::PixelGameEngine* p) 
	: GameState(p) {

	player.pos = { 0, 0 };
	size = 4;
	positions.clear();

	isPaused = false;

	viewMoveMax = 5.0f;
	isChangeState = false;

	for (int i = 0; i < (pge->ScreenWidth() / size) * (int)(pge->ScreenHeight() / size - 4); i++) { positions.push_back(0); }
	positions[0] = true;

	level.Initialize((int)(positions.size() / (player.nSize * player.nSize)));

	level.SetTextPosition({ 0.0f, pge->ScreenHeight() - (3.0f * size + 4.0f) });

	if (LevelManager::Get().GetIsLevelLoaded()) {
		levelArt.Initialize(LevelManager::Get().GetLevelLoaded());
	}
	else if (LevelManager::Get().GetisImageMadeInEditor()) {
		levelArt.Initialize(LevelManager::Get().GetBackImage());
	}
	else {
		levelArt.Initialize(LevelManager::Get().GetSelectedLevel());
	}

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

	if (pge->GetKey(olc::P).bPressed) {
		isPaused = !isPaused;
	}

	if (isPaused) return;

	const olc::Key& dir = (olc::Key)level.GetCurrentDirection();

	uint8_t keyState = olc::NONE;
	/*
	  keyState == 0 => No key is pressed
	  keyState == 1 => Correct key is pressed
	  keyState == 2 => Incorrect key is pressed
	*/
	
	for (uint32_t i = 0; i < nInputs; i++) {
		if (pge->GetKey(inputs[i]).bPressed) {
			if (inputs[i] == dir) {
				keyState = 1;
			}
			else {
				keyState = 2;
			}
		}
	}

	if (keyState == 2) {
		dSpeed += 0.25f;

		viewMove.x = RandomRange(-viewMoveMax, viewMoveMax);
		viewMove.y = RandomRange(-viewMoveMax, viewMoveMax);
	}

	if (keyState == 1) {
		level.Logic({ level.GetTextPosition().x - 10.0f, level.GetTextPosition().y });

		player.Move(pge->ScreenWidth(), pge->ScreenHeight(), 2 * size);

		//Show the pixels at the position of player
		for (int i = 0; i < player.nSize; i++) {
			for (int j = 0; j < player.nSize; j++) {
				SetTile(player.pos.x / size + j, player.pos.y / size + i, true);
			}
		}
	}
}

void PlayState::Logic(float dt) {
	dt = std::fminf(dt, 2.0f);

	if (isChangeState) {
		accumulator += dt;
		
		if (accumulator > 1.0f) SetState(Menu);
	}

	if (level.GetDirections().size() == 0) {
		if (!LevelManager::Get().GetIsLevelLoaded()) LevelManager::Get().SetNextLevelState(true);
		isChangeState = true;
	}

	if (!isChangeState && !isPaused) level.MoveText((speed + dSpeed) * dt);

	if (level.GetTextPosition().x > pge->ScreenWidth()) {
		isChangeState = true;
	}

	viewMove *= 0.99f;
	if (viewMove.x < 0.1f) viewMove.x = 0.0f;
	if (viewMove.y < 0.1f) viewMove.y = 0.0f;
}

void PlayState::Render() {
	//Draw the front sprite
	pge->DrawSprite(0 + viewMove.x, 0 + viewMove.y, levelArt.GetSprite(), size);

	for (int i = 0; i < pge->ScreenHeight() / size - 4; i++) {
		for (int j = 0; j < pge->ScreenWidth() / size; j++) {
			if (positions[i * (pge->ScreenWidth() / size) + j]) continue;

			pge->FillRect(j * size + viewMove.x, i * size + viewMove.y, size, size, olc::BLACK);
		}
	}

	//Draw player
	pge->FillRect(player.pos.x + viewMove.x, player.pos.y + viewMove.y, 2 * size, 2 * size, olc::MAGENTA);

	//Draw the level
	for (int i = 0; i < (int)level.GetDirections().size(); i++) {
		const int& dir = level.GetCurrentDirection(i);

		olc::Pixel color = olc::WHITE;
		if (i == 0) color = olc::RED;

		auto [x, y] = (olc::vi2d)level.GetTextPosition();
		int distance = 10;

		std::string str;

		switch (dir) {
		case olc::RIGHT: str = ">"; break;
		case olc::DOWN:  str = "V"; break;
		case olc::LEFT:  str = "<"; break;
		case olc::UP:    str = "^"; break;
		case olc::W:	 str = "W"; break;
		case olc::A:	 str = "A"; break;
		case olc::S:	 str = "S"; break;
		case olc::D:	 str = "D"; break;
		}

		pge->DrawString(x - i * distance + viewMove.x, y + viewMove.y, std::move(str), color);
	}

	//Draw line and score
	pge->DrawLine(0 + viewMove.x, pge->ScreenHeight() - (4 * size + 1) + viewMove.y, pge->ScreenWidth(), pge->ScreenHeight() - (4 * size + 1), olc::Pixel(200, 200, 200));
	pge->DrawString(0 + viewMove.y, pge->ScreenHeight() - (3 * size - 3) + viewMove.y, "Score: " + std::to_string(level.GetScore()), olc::DARK_CYAN);

	if (isPaused) {
		pge->FillRect(pge->ScreenWidth() / 2 - 32, pge->ScreenHeight() / 2 - 30, 30, 60);
		pge->FillRect(pge->ScreenWidth() / 2 + 4, pge->ScreenHeight() / 2 - 30, 30, 60);
	}
}