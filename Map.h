#pragma once
#include "Player.h"

#define BLANK_TILE '.'
#define COIN_SYMBOL '$'
#define MAP_WIDTH 61
#define MAP_HEIGHT 37
#define MAX_WIDTH 41
#define MAX_HEIGHT 21
#define MAP_VISION 8
#define HORIZONTAL 0
#define VERTICAL 1
#define X 0
#define Y 1

enum Direction { UP, DOWN, LEFT, RIGHT };

class Map {
public:
	int width = MAP_WIDTH;
	int height = MAP_HEIGHT;
	char tiles[MAP_HEIGHT][MAP_WIDTH];
	bool light;
	int vision;

};

void drawLines(Map& map, int lines, int maxLineWidth, char tileSymbol = NULL, short direction = HORIZONTAL);
void drawCoins(Map& map, int coinNumber);
void createMap(Map& map);
int tileDistance(Player player, int x, int y, short xy = -1);
bool tileVisible(Map map, Player player, int x, int y);
void drawMap(Player player, Map map);
void resetMap(Player& player, Map& map, bool light, short vision = MAP_VISION);
bool canMove(char tile);
void checkCoin(Map map, Player& player);
void checkMove(Map& map, Player& player, int x, int y, char playerSymbol);
void move(Direction direction, Map& map, Player& player);
