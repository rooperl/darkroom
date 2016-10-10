#pragma once

const char PLAYER_UP = '^';
const char PLAYER_DOWN = 'v';
const char PLAYER_LEFT = '<';
const char PLAYER_RIGHT = '>';

enum Direction { UP, DOWN, LEFT, RIGHT };

class Player {
public:
	short x;
	short y;
	short coins;
	Direction direction;
};
