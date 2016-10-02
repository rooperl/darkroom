#include <ctime>
#include <windows.h>
#include <chrono>
#include <string>
#include <thread>

#include "Game.h"
#include "Map.h"

void wait(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void init(Player& player, Map& map) {
	srand((unsigned)time(NULL));
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	resetMap(player, map);
	map.light = false;
}

void setCursor(short y, short x) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
}

std::string fillTextBuffer() {
	setCursor(MAX_HEIGHT);
	std::string text;
	for (int space = 0; space < MAX_WIDTH; space++)
		text += " ";
	return text;
}

bool windowFocused() {
	return GetConsoleWindow() == GetForegroundWindow();
}

bool toggleKey(short VK) {
	return GetAsyncKeyState(VK) & 0x8000 != 0;
}

void checkKeyPresses(Game& game, Map& map, Player& player) {
	if (GetAsyncKeyState(VK_UP)) move(UP, map, player);
	if (GetAsyncKeyState(VK_DOWN)) move(DOWN, map, player);
	if (GetAsyncKeyState(VK_LEFT)) move(LEFT, map, player);
	if (GetAsyncKeyState(VK_RIGHT)) move(RIGHT, map, player);
	if (toggleKey(VK_ESCAPE)) game.quit = true;
	if (toggleKey('L')) map.light = !map.light;
	if (toggleKey('R')) resetMap(player, map);
}
