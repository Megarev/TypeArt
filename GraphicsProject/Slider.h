#pragma once
#include "olcPixelGameEngine.h"

class Slider {
private:
	olc::vi2d sliderPos;
	olc::vi2d pointPos;
	olc::Sprite* slider = nullptr;
	olc::Decal* decal = nullptr;
	olc::Pixel currentColor;
	float value, maxValue;

	bool IsPointInSprite(const olc::vi2d& point) {
		return (
			point.x > sliderPos.x && point.x < sliderPos.x + slider->width &&
			point.y > sliderPos.y && point.y < sliderPos.y + slider->height
			);
	}

	olc::Pixel GetColor(const olc::vi2d& point, int pos = 0) {
		if (IsPointInSprite(point)) {
			pointPos.x = point.x;
			return slider->GetPixel(point.x, pos);
		}

		return olc::BLANK;
	}

	float GetValueInSlider(const olc::vi2d& point, int pos = 0) {
		if (IsPointInSprite(point)) {
			return (std::fabsf(point.x - sliderPos.x) / slider->width) * maxValue;
		}

		return -1.0f;
	}
public:
	Slider() {}
	Slider(const olc::vi2d& pos, const std::string& filepath, float valueMax, float initValue = 0.0f)
		: sliderPos(pos), maxValue(valueMax), value(initValue) {

		slider = new olc::Sprite(filepath);
		decal = new olc::Decal(slider);
		currentColor = olc::WHITE;

		pointPos = { pos.x, pos.y + slider->height };
	}

	void Input(olc::PixelGameEngine* pge, int pos = 0) {
		if (pge->GetMouse(0).bHeld) {
			olc::Pixel color = GetColor({ pge->GetMouseX(), pge->GetMouseY() }, pos);
			if (color != olc::BLANK) {
				currentColor = color;
			}
			float initValue = GetValueInSlider({ pge->GetMouseX(), pge->GetMouseY() }, pos);
			if (initValue >= 0.0f) {
				value = initValue;
			}
		}
	}

	void Render(olc::PixelGameEngine* pge, olc::Pixel color = olc::WHITE) {
		//pge->DrawSprite(sliderPos, slider);
		pge->DrawDecal(sliderPos, decal, { 1.0f, 1.0f }, color);
		pge->FillTriangle(pointPos.x, pointPos.y, pointPos.x - 2, pointPos.y + 4, pointPos.x + 2, pointPos.y + 4, currentColor);

		//pge->FillRect(25, 25, 25, 25, currentColor);
	}

	olc::Pixel GetCurrentColor() const { return currentColor; }
	float GetValue() const { return value; }
};