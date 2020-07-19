#pragma once

//Speeds of texts
extern float speedEasy, speedMedium, speedHard;
extern float speed; //Current speed of text (Playstate)

//Text types
extern uint8_t textType;
/*
	textType == 0 => Text type is arrow keys
	textType == 1 => Text type is WASD
	textType == 2 => Text type is arrow keys + WASD
*/