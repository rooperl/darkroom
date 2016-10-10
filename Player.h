<<<<<<< HEAD
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
=======
#pragma once

const char PLAYER_UP = '^';
const char PLAYER_DOWN = 'v';
const char PLAYER_LEFT = '<';
const char PLAYER_RIGHT = '>';

enum Direction { UP, DOWN, LEFT, RIGHT };

class Player {
public:
	int x;
	int y;
	int coins;
	Direction direction;
};
>>>>>>> 670d61cc465dd8818df27b98dc19b6bdb4ec15cf
