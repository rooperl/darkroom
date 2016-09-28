#include "DarkRoom.h"
#include <chrono>
#include <thread>

bool quit = false;

void wait(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void fillTextBuffer(int spaces) {
	for (int space = 0; space <= spaces; space++)
		std::cout << " ";
}

void init() {
	srand((unsigned)time(NULL));
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	createMap();
	player.x = map.width / 2, player.y = map.height / 2;
	map.light = false;
	map.tiles[player.y][player.x] = 'v';
	drawMap();
}

bool toggleKey(short VK) {
	return GetAsyncKeyState(VK) & 0x8000 != 0;
}

bool windowFocused() {
	return GetConsoleWindow() == GetForegroundWindow();
}

void checkKeyPresses() {
	if (GetAsyncKeyState(VK_UP)) move(UP);
	if (GetAsyncKeyState(VK_DOWN)) move(DOWN);
	if (GetAsyncKeyState(VK_LEFT)) move(LEFT);
	if (GetAsyncKeyState(VK_RIGHT)) move(RIGHT);
	if (toggleKey(VK_ESCAPE)) quit = true;
	if (toggleKey('L')) map.light = !map.light;
	if (toggleKey('R')) {
		createMap();
		player.x = map.width / 2, player.y = map.height / 2;
		map.tiles[player.y][player.x] = 'v';
	}
}

int main() {
	init();
	while (true) {
		clearScreen();
		drawMap();
		if (map.light)
			std::cout << "You have turned the lights on.";
		else
			std::cout << "You're in a dark room.";
		fillTextBuffer(50);
		std::cout << "\n\nCoins: " << player.coins << "\n\n";
		wait(50);
		if (windowFocused()) checkKeyPresses();
		if (quit) return 0;
	}
}