#pragma once

#include <iostream>
#include <ctime>
#include <windows.h>
#include <chrono>
#include <thread>

#include "Map.h"

class Game {
public:
	bool quit;
} game;

class Player {
public:
	int x;
	int y;
	int coins;
} player;

void wait(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
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
	resetMap();
	map.light = false;
}

bool windowFocused() {
	return GetConsoleWindow() == GetForegroundWindow();
}

bool toggleKey(short VK) {
	return GetAsyncKeyState(VK) & 0x8000 != 0;
}

void checkKeyPresses() {
	if (GetAsyncKeyState(VK_UP)) move(UP);
	if (GetAsyncKeyState(VK_DOWN)) move(DOWN);
	if (GetAsyncKeyState(VK_LEFT)) move(LEFT);
	if (GetAsyncKeyState(VK_RIGHT)) move(RIGHT);
	if (toggleKey(VK_ESCAPE)) game.quit = true;
	if (toggleKey('L')) map.light = !map.light;
	if (toggleKey('R')) resetMap(true);
}
