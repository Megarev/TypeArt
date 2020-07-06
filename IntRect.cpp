#include "IntRect.h"

IntRect::IntRect() {}

IntRect::IntRect(int x, int y, int w, int h) {
	pos = { x, y };
	size = { w, h };
}

bool IntRect::IsPointInBounds(const olc::vi2d& point) {
	return (point.x > pos.x && point.y > pos.y && point.x < (pos.x + size.x) && point.y < (pos.y + size.y));
}

void IntRect::SetPosition(const olc::vi2d& p) {
	pos = p;
}

void IntRect::SetSize(const olc::vi2d& s) {
	size = s;
}

olc::vi2d IntRect::GetPosition() const {
	return pos;
}

olc::vi2d IntRect::GetSize() const {
	return size;
}