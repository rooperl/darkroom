#include <iostream>
#include "Game.h"
#include "Map.h"

void drawLines(Map& map, int lines, int maxLineWidth, char tileSymbol, short direction) {
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

void drawCoins(Map& map, int coinNumber) {
	for (int coin = 0; coin <= coinNumber; coin++) {
		int x = rand() % map.width + 1;
		int y = rand() % map.height + 1;
		map.tiles[y][x] = COIN_SYMBOL;
	}
}

void createMap(Map& map) {
	int x, y;
	for (x = 0; x <= map.width; x++)
		for (y = 0; y <= map.height; y++)
			map.tiles[y][x] = NULL;

	int horizontalWalls = rand() % (map.height / 2) + 2;
	int verticalWalls = rand() % (map.width / 2) + 2;
	int horizontalCorridors = rand() % (map.height / 2) + 2;
	int verticalCorridors = rand() % (map.width / 2) + 2;
	int coinNumber = rand() % (map.width * map.height) / 100 + 1;

	drawLines(map, horizontalWalls, 1, '#');
	drawLines(map, verticalWalls, 1, '#', VERTICAL);
	drawLines(map, horizontalCorridors, 3);
	drawLines(map, verticalCorridors, 3, NULL, VERTICAL);

	drawCoins(map, coinNumber);

	for (x = 0; x < map.width; x++)
		map.tiles[0][x] = '#';
	for (x = 0; x < map.width; x++)
		map.tiles[map.height - 1][x] = '#';
	for (y = 0; y < map.height; y++)
		map.tiles[y][0] = '#';
	for (y = 0; y < map.height; y++)
		map.tiles[y][map.width - 1] = '#';
}

int tileDistance(Player player, int x, int y, short xy) {
	if (xy == X) return abs(x - player.x);
	if (xy == Y) return abs(y - player.y);
	return abs(x - player.x) + abs(y - player.y);
}

bool tileVisible(Map map, Player player, int x, int y) {
	if ((tileDistance(player, x, y, X) == map.vision || tileDistance(player, x, y, Y) == 8) && !map.light) return false;
	if (tileDistance(player, x, y) <= map.vision || map.light) return true;
	return false;
}

void drawMap(Player player, Map map) {
	int x, y;
	setCursor();
	for (y = player.y - (MAX_HEIGHT / 2); y < player.y + (MAX_HEIGHT / 2); y++) {
		for (x = player.x - (MAX_WIDTH / 2); x < player.x + (MAX_WIDTH / 2); x++) {
			if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) std::cout << BLANK_TILE;
			else if (tileVisible(map, player, x, y)) std::cout << map.tiles[y][x];
			else std::cout << BLANK_TILE;
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void resetMap(Player& player, Map& map, bool light, short vision) {
	createMap(map);
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

void checkCoin(Map map, Player& player) {
	if (map.tiles[player.y][player.x] == '$') player.coins++;
}

void checkMove(Map& map, Player& player, int x, int y, char playerSymbol) {
	if (canMove(map.tiles[player.y + y][player.x + x])) {
		map.tiles[player.y][player.x] = NULL;
		player.x += x;
		player.y += y;
		checkCoin(map, player);
	}
	map.tiles[player.y][player.x] = playerSymbol;
}

void move(Direction direction, Map& map, Player& player) {
	switch (direction) {
	case UP: checkMove(map, player, 0, -1, '^');
		break;
	case DOWN: checkMove(map, player, 0, 1, 'v');
		break;
	case LEFT: checkMove(map, player, -1, 0, '<');
		break;
	case RIGHT: checkMove(map, player, 1, 0, '>');
		break;
	}
}
