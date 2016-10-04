#pragma once

#define PLAYER_UP '^'
#define PLAYER_DOWN 'v'
#define PLAYER_LEFT '<'
#define PLAYER_RIGHT '>'

enum Direction { UP, DOWN, LEFT, RIGHT };

class Player {
public:
	int x;
	int y;
	int coins;
	Direction direction;
};
