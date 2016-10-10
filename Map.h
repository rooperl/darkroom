#pragma once
#include "Player.h"

const char BLANK_TILE = '.';
const char WALL_TILE = '#';
const char COIN_SYMBOL = '$';

const short MAP_WIDTH = 61;
const short MAP_HEIGHT = 37;
const short  MAX_WIDTH = 41;
const short MAX_HEIGHT = 21;
const short MAP_VISION = 8;

const short HORIZONTAL = 1;
const short VERTICAL = 0;
const short X = 1;
const short Y = 0;

class Map {
public:
	short width = MAP_WIDTH;
	short height = MAP_HEIGHT;
	char tiles[MAP_HEIGHT][MAP_WIDTH];
	bool light;
	bool quit;
	short vision;

};

void drawLines(Map& map, short lines, short maxLineWidth, char tileSymbol = NULL, short direction = HORIZONTAL);
void drawCoins(Map& map, short coinNumber);
void createMap(Map& map);
short tileDistance(Player player, short x, short y, short xy = -1);
bool tileVisible(Map map, Player player, short x, short y);
void drawMap(Player player, Map map);
void resetMap(Player& player, Map& map, bool light = false, short vision = MAP_VISION);
bool canMove(char tile);
void checkCoin(Map map, Player& player);
void checkMove(Map& map, Player& player, short x, short y, Direction direction);
void move(Direction direction, Map& map, Player& player);
bool isPlayerTile(char tile);
char getPlayerTile(Direction direction);
