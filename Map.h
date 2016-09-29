#pragma once

#define MAP_WIDTH 50
#define MAP_HEIGHT 30
#define MAX_WIDTH 41
#define MAX_HEIGHT 21
#define H 0
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

enum Direction { UP, DOWN, LEFT, RIGHT };

void clearScreen() {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
}

void drawLines(int lines, int maxLineWidth, char tileSymbol = NULL, int direction = -1) {
	int wallLength, wallX, wallY, lineNumber, tileNumber;
	for (int line = 0; line <= lines; line++) {
		direction == H ? wallLength = rand() % (map.width / 2) + 1 :
			wallLength = rand() % (map.height / 2) + 1;
		wallX = rand() % (map.width) + 1;
		wallY = rand() % (map.height) + 1;
		maxLineWidth = rand() % maxLineWidth + 1;
		for (lineNumber = 0; lineNumber < maxLineWidth; lineNumber++) {
			if (rand() % 2 == 0)
				for (tileNumber = 0; tileNumber <= wallLength; tileNumber++)
					direction == H ? map.tiles[wallY + lineNumber][wallX + tileNumber] = tileSymbol :
					map.tiles[wallY + tileNumber][wallX + lineNumber] = tileSymbol;
			else
				for (tileNumber = wallLength; tileNumber > 0; tileNumber--)

					direction == H ? map.tiles[wallY + lineNumber][map.width - tileNumber] = tileSymbol :
					map.tiles[wallY + map.height - tileNumber][wallX + lineNumber] = tileSymbol;
		}
	}
}

void drawCoins(int coinNumber) {
	for (int coin = 0; coin <= coinNumber; coin++) {
		int x = rand() % map.width + 1;
		int y = rand() % map.height + 1;
		map.tiles[y][x] = '$';
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

	drawLines(horizontalWalls, 1, '#', H);
	drawLines(verticalWalls, 1, '#');
	drawLines(horizontalCorridors, 3, H);
	drawLines(verticalCorridors, 3);
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

int mapCoordinate(int xy) {
	if (xy = X)
		if (MAP_WIDTH <= MAX_WIDTH) return 0;
		else return (player.x - (MAX_WIDTH / 2));
	else
		if (MAP_HEIGHT <= MAX_HEIGHT) return 0;
		else return (player.y - (MAX_HEIGHT / 2));
	return 0;
}

void drawMap() {
	int x, y;
	clearScreen();
	for (y = mapCoordinate(Y); y < mapCoordinate(Y) + (MAP_HEIGHT > MAX_HEIGHT ? MAX_HEIGHT : MAP_HEIGHT); y++) {
		for (x = mapCoordinate(X); x < mapCoordinate(Y) + (MAP_WIDTH > MAX_WIDTH ? MAX_WIDTH : MAP_WIDTH); x++) {
			if (x < 0 || y < 0 || x >= MAX_WIDTH || y >= MAX_HEIGHT ) std::cout << ' ';
			else if (tileVisible(x, y)) std::cout << map.tiles[y][x];
			else std::cout << ' ';
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void resetMap(bool light = false, int vision = 8) {
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
