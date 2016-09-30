#pragma once

#include "Game.h"

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

class Map {
public:
	int width = MAP_WIDTH;
	int height = MAP_HEIGHT;
	char tiles[MAP_HEIGHT][MAP_WIDTH];
	bool light;
	int vision;
	
} map;

class Player {
public:
	int x;
	int y;
	int coins;
} player;

enum Direction { UP, DOWN, LEFT, RIGHT };

void setCursor(short y = 0, short x = 0) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
}

std::string fillTextBuffer() {
	setCursor(MAX_HEIGHT);
	std::string text;
	for (int space = 0; space < MAX_WIDTH; space++)
		text += " ";
	return text;
}

void drawLines(int lines, int maxLineWidth, char tileSymbol = NULL, short direction = HORIZONTAL) {
	int wallLength, wallX, wallY, lineNumber, tileNumber;
	for (int line = 0; line <= lines; line++) {
		direction == HORIZONTAL ? wallLength = rand() % (map.width / 2) + 1 :
			wallLength = rand() % (map.height / 2) + 1;
		wallX = rand() % (map.width) + 1;
		wallY = rand() % (map.height) + 1;
		maxLineWidth = rand() % maxLineWidth + 1;
		for (lineNumber = 0; lineNumber < maxLineWidth; lineNumber++) {
			if (rand() % 2 == 0)
				for (tileNumber = 0; tileNumber <= wallLength; tileNumber++)
					direction == HORIZONTAL ? map.tiles[wallY + lineNumber][wallX + tileNumber] = tileSymbol :
					map.tiles[wallY + tileNumber][wallX + lineNumber] = tileSymbol;
			else
				for (tileNumber = wallLength; tileNumber > 0; tileNumber--)

					direction == HORIZONTAL ? map.tiles[wallY + lineNumber][map.width - tileNumber] = tileSymbol :
					map.tiles[wallY + map.height - tileNumber][wallX + lineNumber] = tileSymbol;
		}
	}
}

void drawCoins(int coinNumber) {
	for (int coin = 0; coin <= coinNumber; coin++) {
		int x = rand() % map.width + 1;
		int y = rand() % map.height + 1;
		map.tiles[y][x] = COIN_SYMBOL;
	}
}

void createMap() {
	int x, y;
	for (x = 0; x <= map.width; x++)
		for (y = 0; y <= map.height; y++)
			map.tiles[y][x] = NULL;

	int horizontalWalls = rand() % (map.height / 2) + 2;
	int verticalWalls = rand() % (map.width / 2) + 2;
	int horizontalCorridors = rand() % (map.height / 2) + 2;
	int verticalCorridors = rand() % (map.width / 2) + 2;
	int coinNumber = rand() % (map.width * map.height) / 100 + 1;

	drawLines(horizontalWalls, 1, '#');
	drawLines(verticalWalls, 1, '#', VERTICAL);
	drawLines(horizontalCorridors, 3);
	drawLines(verticalCorridors, 3, NULL, VERTICAL);
	drawCoins(coinNumber);

	for (x = 0; x < map.width; x++)
		map.tiles[0][x] = '#';
	for (x = 0; x < map.width; x++)
		map.tiles[map.height-1][x] = '#';
	for (y = 0; y < map.height; y++)
		map.tiles[y][0] = '#';
	for (y = 0; y < map.height; y++)
		map.tiles[y][map.width-1] = '#';
}

int tileDistance(int x, int y, short xy = -1) {
	if (xy == X) return abs(x - player.x);
	if (xy == Y) return abs(y - player.y);
	return abs(x - player.x) + abs(y - player.y);
}

bool tileVisible(int x, int y) {
	if ((tileDistance(x, y, X) == map.vision || tileDistance(x, y, Y) == 8) && !map.light) return false;
	if (tileDistance(x, y) <= map.vision || map.light) return true;
	return false;
}

void drawMap() {
	int x, y;
	setCursor();
	for (y = player.y - (MAX_HEIGHT / 2); y < player.y + (MAX_HEIGHT / 2); y++) {
		for (x = player.x - (MAX_WIDTH / 2); x < player.x + (MAX_WIDTH / 2); x++) {
			if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT ) std::cout << BLANK_TILE;
			else if (tileVisible(x, y)) std::cout << map.tiles[y][x];
			else std::cout << BLANK_TILE;
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void resetMap(bool light = false, short vision = MAP_VISION) {
	createMap();
	player.x = map.width / 2, player.y = map.height / 2;
	map.tiles[player.y][player.x] = 'v';
	map.light = light;
	map.vision = vision;
}

bool canMove(char tile) {
	if (tile == NULL) return true;
	if (tile == '$') return true;
	else return false;
}

void checkCoin() {
	if (map.tiles[player.y][player.x] == '$') player.coins++;
}

void checkMove(int x, int y, char playerSymbol) {
	if (canMove(map.tiles[player.y + y][player.x + x])) {
		map.tiles[player.y][player.x] = NULL;
		player.x += x;
		player.y += y;
		checkCoin();
	}
	map.tiles[player.y][player.x] = playerSymbol;
}

void move(Direction direction) {
	switch (direction) {
	case UP: checkMove(0, -1, '^');
		break;
	case DOWN: checkMove(0, 1, 'v');
		break;
	case LEFT: checkMove(-1, 0, '<');
		break;
	case RIGHT: checkMove(1, 0, '>');
		break;
	}
}
