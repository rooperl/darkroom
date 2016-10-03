#pragma once

enum Direction { UP, DOWN, LEFT, RIGHT };

class Player {
public:
	int x;
	int y;
	int coins;
	Direction direction;
};
