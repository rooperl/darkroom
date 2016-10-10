<<<<<<< HEAD
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Map.h"

void drawLines(Map& map, short lines, short maxLineWidth, char tileSymbol, short direction) {
	short line, wallLength, wallX, wallY, lineNumber, tileNumber;
	for (line = 0; line <= lines; line++) {
		direction == HORIZONTAL ? wallLength = rand() % (map.width / 2) + 1 :
			wallLength = rand() % (map.height / 2) + 1;
		wallX = rand() % (map.width) + 1;
		wallY = rand() % (map.height) + 1;
		maxLineWidth = rand() % maxLineWidth + 1;
		for (lineNumber = 0; lineNumber < maxLineWidth; lineNumber++) {
			if (rand() % 2 == 0)
				for (tileNumber = 0; tileNumber <= wallLength; tileNumber++)
					direction == HORIZONTAL ? map.tiles[wallY + lineNumber][wallX + tileNumber]
					= tileSymbol : map.tiles[wallY + tileNumber][wallX + lineNumber] = tileSymbol;
			else
				for (tileNumber = wallLength; tileNumber > 0; tileNumber--)
					direction == HORIZONTAL ? map.tiles[wallY + lineNumber][map.width - tileNumber]
					= tileSymbol : map.tiles[wallY + map.height - tileNumber][wallX + lineNumber] = tileSymbol;
		}
	}
}

void drawCoins(Map& map, short coinNumber) {
	for (short coin = 0; coin <= coinNumber; coin++) {
		short x = rand() % map.width + 1;
		short y = rand() % map.height + 1;
		map.tiles[y][x] = COIN_SYMBOL;
	}
}

void createMap(Map& map) {
	short x, y;
	for (x = 0; x <= map.width; x++)
		for (y = 0; y <= map.height; y++)
			map.tiles[y][x] = NULL;

	short horizontalWalls = rand() % (map.height / 2) + 2;
	short verticalWalls = rand() % (map.width / 2) + 2;
	short horizontalCorridors = rand() % (map.height / 2) + 2;
	short verticalCorridors = rand() % (map.width / 2) + 2;
	short coinNumber = rand() % (map.width * map.height) / 100 + 1;

	drawLines(map, horizontalWalls, 1, WALL_TILE);
	drawLines(map, verticalWalls, 1, WALL_TILE, VERTICAL);
	drawLines(map, horizontalCorridors, 3);
	drawLines(map, verticalCorridors, 3, NULL, VERTICAL);

	drawCoins(map, coinNumber);

	for (x = 0; x < map.width; x++)
		map.tiles[0][x] = WALL_TILE;
	for (x = 0; x < map.width; x++)
		map.tiles[map.height - 1][x] = WALL_TILE;
	for (y = 0; y < map.height; y++)
		map.tiles[y][0] = WALL_TILE;
	for (y = 0; y < map.height; y++)
		map.tiles[y][map.width - 1] = WALL_TILE;
}

short tileDistance(Player player, short x, short y, short xy) {
	if (xy == X) return abs(x - player.x);
	if (xy == Y) return abs(y - player.y);
	return abs(x - player.x) + abs(y - player.y);
}

bool tileVisible(Map map, Player player, short x, short y) {
	if ((tileDistance(player, x, y, X) == map.vision
		|| tileDistance(player, x, y, Y) == 8) && !map.light) return false;
	if (tileDistance(player, x, y) <= map.vision || map.light) return true;
	return false;
}

void drawMap(Player player, Map map) {
	setCursor();
	for (short y = player.y - (MAX_HEIGHT / 2); y < player.y + (MAX_HEIGHT / 2); y++) {
		for (short x = player.x - (MAX_WIDTH / 2); x < player.x + (MAX_WIDTH / 2); x++) {
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
	map.tiles[player.y][player.x] = getPlayerTile(DOWN);
	map.light = light;
	map.vision = vision;
}

bool canMove(char tile) {
	if (tile == NULL) return true;
	if (tile == COIN_SYMBOL) return true;
	else return false;
}

void checkCoin(Map map, Player& player) {
	if (map.tiles[player.y][player.x] == COIN_SYMBOL) player.coins++;
}

void checkMove(Map& map, Player& player, short x, short y, Direction direction) {
	if (canMove(map.tiles[player.y + y][player.x + x])) {
		map.tiles[player.y][player.x] = NULL;
		player.x += x;
		player.y += y;
		checkCoin(map, player);
	}
	map.tiles[player.y][player.x] = getPlayerTile(direction);
	player.direction = direction;
}

void move(Direction direction, Map& map, Player& player) {
	switch (direction) {
	case UP: checkMove(map, player, 0, -1, UP);
		break;
	case DOWN: checkMove(map, player, 0, 1, DOWN);
		break;
	case LEFT: checkMove(map, player, -1, 0, LEFT);
		break;
	case RIGHT: checkMove(map, player, 1, 0, RIGHT);
		break;
	}
}

bool isPlayerTile(char tile) {
	if (tile == getPlayerTile(UP) || tile == getPlayerTile(DOWN)
		|| tile == getPlayerTile(LEFT) || tile == getPlayerTile(RIGHT)) return true;
	return false;
}

char getPlayerTile(Direction direction) {
	switch (direction) {
	case UP: return PLAYER_UP;
		break;
	case DOWN: return PLAYER_DOWN;
		break;
	case LEFT: return PLAYER_LEFT;
		break;
	case RIGHT: return PLAYER_RIGHT;
		break;
	}
	return BLANK_TILE;
}
=======
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Map.h"

void drawLines(Map& map, short lines, short maxLineWidth, char tileSymbol, short direction) {
	short line, wallLength, wallX, wallY, lineNumber, tileNumber;
	for (line = 0; line <= lines; line++) {
		direction == HORIZONTAL ? wallLength = rand() % (map.width / 2) + 1 :
			wallLength = rand() % (map.height / 2) + 1;
		wallX = rand() % (map.width) + 1;
		wallY = rand() % (map.height) + 1;
		maxLineWidth = rand() % maxLineWidth + 1;
		for (lineNumber = 0; lineNumber < maxLineWidth; lineNumber++) {
			if (rand() % 2 == 0)
				for (tileNumber = 0; tileNumber <= wallLength; tileNumber++)
					direction == HORIZONTAL ? map.tiles[wallY + lineNumber][wallX + tileNumber]
					= tileSymbol : map.tiles[wallY + tileNumber][wallX + lineNumber] = tileSymbol;
			else
				for (tileNumber = wallLength; tileNumber > 0; tileNumber--)
					direction == HORIZONTAL ? map.tiles[wallY + lineNumber][map.width - tileNumber]
					= tileSymbol : map.tiles[wallY + map.height - tileNumber][wallX + lineNumber] = tileSymbol;
		}
	}
}

void drawCoins(Map& map, short coinNumber) {
	for (short coin = 0; coin <= coinNumber; coin++) {
		short x = rand() % map.width + 1;
		short y = rand() % map.height + 1;
		map.tiles[y][x] = COIN_SYMBOL;
	}
}

void createMap(Map& map) {
	short x, y;
	for (x = 0; x <= map.width; x++)
		for (y = 0; y <= map.height; y++)
			map.tiles[y][x] = NULL;

	short horizontalWalls = rand() % (map.height / 2) + 2;
	short verticalWalls = rand() % (map.width / 2) + 2;
	short horizontalCorridors = rand() % (map.height / 2) + 2;
	short verticalCorridors = rand() % (map.width / 2) + 2;
	short coinNumber = rand() % (map.width * map.height) / 100 + 1;

	drawLines(map, horizontalWalls, 1, WALL_TILE);
	drawLines(map, verticalWalls, 1, WALL_TILE, VERTICAL);
	drawLines(map, horizontalCorridors, 3);
	drawLines(map, verticalCorridors, 3, NULL, VERTICAL);

	drawCoins(map, coinNumber);

	for (x = 0; x < map.width; x++)
		map.tiles[0][x] = WALL_TILE;
	for (x = 0; x < map.width; x++)
		map.tiles[map.height - 1][x] = WALL_TILE;
	for (y = 0; y < map.height; y++)
		map.tiles[y][0] = WALL_TILE;
	for (y = 0; y < map.height; y++)
		map.tiles[y][map.width - 1] = WALL_TILE;
}

int tileDistance(Player player, short x, short y, short xy) {
	if (xy == X) return abs(x - player.x);
	if (xy == Y) return abs(y - player.y);
	return abs(x - player.x) + abs(y - player.y);
}

bool tileVisible(Map map, Player player, short x, short y) {
	if ((tileDistance(player, x, y, X) == map.vision
		|| tileDistance(player, x, y, Y) == 8) && !map.light) return false;
	if (tileDistance(player, x, y) <= map.vision || map.light) return true;
	return false;
}

void drawMap(Player player, Map map) {
	setCursor();
	for (short y = player.y - (MAX_HEIGHT / 2); y < player.y + (MAX_HEIGHT / 2); y++) {
		for (short x = player.x - (MAX_WIDTH / 2); x < player.x + (MAX_WIDTH / 2); x++) {
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
	map.tiles[player.y][player.x] = getPlayerTile(DOWN);
	map.light = light;
	map.vision = vision;
}

bool canMove(char tile) {
	if (tile == NULL) return true;
	if (tile == COIN_SYMBOL) return true;
	else return false;
}

void checkCoin(Map map, Player& player) {
	if (map.tiles[player.y][player.x] == COIN_SYMBOL) player.coins++;
}

void checkMove(Map& map, Player& player, short x, short y, Direction direction) {
	if (canMove(map.tiles[player.y + y][player.x + x])) {
		map.tiles[player.y][player.x] = NULL;
		player.x += x;
		player.y += y;
		checkCoin(map, player);
	}
	map.tiles[player.y][player.x] = getPlayerTile(direction);
	player.direction = direction;
}

void move(Direction direction, Map& map, Player& player) {
	switch (direction) {
	case UP: checkMove(map, player, 0, -1, UP);
		break;
	case DOWN: checkMove(map, player, 0, 1, DOWN);
		break;
	case LEFT: checkMove(map, player, -1, 0, LEFT);
		break;
	case RIGHT: checkMove(map, player, 1, 0, RIGHT);
		break;
	}
}

bool isPlayerTile(char tile) {
	if (tile == getPlayerTile(UP) || tile == getPlayerTile(DOWN)
		|| tile == getPlayerTile(LEFT) || tile == getPlayerTile(RIGHT)) return true;
	return false;
}

char getPlayerTile(Direction direction) {
	switch (direction) {
	case UP: return PLAYER_UP;
		break;
	case DOWN: return PLAYER_DOWN;
		break;
	case LEFT: return PLAYER_LEFT;
		break;
	case RIGHT: return PLAYER_RIGHT;
		break;
	}
	return BLANK_TILE;
}
>>>>>>> 670d61cc465dd8818df27b98dc19b6bdb4ec15cf
