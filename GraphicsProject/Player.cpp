#include "Player.h"

Player::Player() {
	direction = 1; 
	nSize = 2;
}

void Player::Move(int w, int h, int pixelSize) {
	pos.x += pixelSize * direction;

	if (pos.x > w - pixelSize) {
		pos.x -= pixelSize;
		pos.y += pixelSize;
		direction = -1;
	}
	else if (pos.x < 0) {
		pos.x += pixelSize;
		pos.y += pixelSize;
		direction = 1;
	}

	if (pos.y > h - 3 * pixelSize) {
		pos.y -= pixelSize;
	}
}