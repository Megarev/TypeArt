#include "EditorState.h"

EditorState::EditorState(olc::PixelGameEngine* p)
	: GameState(p) {
	isGridShown = false;
	size = 4;
	sprite = new olc::Sprite(32, 32);

	HSVSlider[0] = Slider({ 4, pge->ScreenHeight() - 15 }, "files/images/colors.png", 360.0f, 1.0f);
	HSVSlider[1] = Slider({ 4, pge->ScreenHeight() - 10 }, "files/images/saturation.png", 1.0f, 1.0f);
	HSVSlider[2] = Slider({ 4, pge->ScreenHeight() - 5 },  "files/images/value.png", 1.0f, 1.0f);
}

void EditorState::DrawGrid(int x1, int y1, int x2, int y2, int distance, olc::Pixel color) {
	// distance is the spacing between two lines

	size = distance;

	olc::vi2d length = {
		(int)std::fabs(x2 - x1), (int)std::fabs(y2 - y1)
	};

	for (int i = 0; i < length.x / distance + 1; i++) {
		pge->DrawLine(x1 + i * distance, y1, x1 + i * distance, y2, color);
	}

	for (int i = 0; i < length.y / distance + 1; i++) {
		pge->DrawLine(x1, y1 + i * distance, x2, y1 + i * distance, color);
	}
}

void EditorState::Input() {
	if (pge->GetKey(olc::G).bPressed) {
		isGridShown = !isGridShown;
	}

	if (pge->GetKey(olc::ENTER).bReleased) {
		LevelManager::Get().SaveSprite(sprite->GetData());
		LevelManager::Get().GetisImageMadeInEditor() = true;
		SetState(State::Play);
	}

	if (pge->GetMouse(0).bHeld) {
		if (pge->GetMouseY() < pge->ScreenHeight() - 17) {
			auto [posX, posY] = olc::vi2d(pge->GetMouseX() / size, pge->GetMouseY() / size);
			auto color = olc::Colours::FromHsv(HSVSlider[0].GetValue(), HSVSlider[1].GetValue(), HSVSlider[2].GetValue());
			sprite->SetPixel(posX, posY, color);

			/*float hue = HSVSlider[0].GetValue();
			float saturation = HSVSlider[1].GetValue();
			float value = HSVSlider[2].GetValue();
			
			std::cout << "Hue : " << hue << std::endl;
			std::cout << "Saturation : " << saturation << std::endl;
			std::cout << "Value : " << value << std::endl;*/
		}
		for (int i = 0; i < 3; i++) {
			HSVSlider[i].Input(pge, 1);
		}
	}
	else if (pge->GetMouse(1).bHeld) {
		if (pge->GetMouseY() < pge->ScreenHeight() - 17) {
			auto [posX, posY] = olc::vi2d(pge->GetMouseX() / size, pge->GetMouseY() / size);
			sprite->SetPixel(posX, posY, olc::BLANK);
		}
	}
}

void EditorState::Logic(float dt) {

}

void EditorState::Render() {
	pge->DrawSprite(0, 0, sprite, size);
	if (isGridShown) DrawGrid(0, 0, pge->ScreenWidth(), pge->ScreenHeight() - 17, 4, olc::Pixel(255, 255, 255, 100));
	
	//for (int i = 0; i < 3; i++) {
	//	HSVSlider[i].Render(pge);
	//}

	HSVSlider[0].Render(pge);
	HSVSlider[1].Render(pge, HSVSlider[0].GetCurrentColor());
	HSVSlider[2].Render(pge, HSVSlider[0].GetCurrentColor());
}

EditorState::~EditorState() {
	delete sprite;
}