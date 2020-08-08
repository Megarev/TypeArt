#pragma once
#include "olcPixelGameEngine.h"

class IntRect {
private:
	olc::vi2d pos, size;
public:
	IntRect();
	IntRect(int x, int y, int w, int h);

	bool IsPointInBounds(const olc::vi2d& point);

	void SetPosition(const olc::vi2d& p);
	void SetSize(const olc::vi2d& s);

	olc::vi2d GetPosition() const;
	olc::vi2d GetSize() const;
};