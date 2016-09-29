#pragma once

#include <iostream>
#include <ctime>
#include <windows.h>

#include "Player.h"
#include "Map.h"

class Game {
public:
	bool quit = false;
} game;

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
	if (toggleKey('R')) resetMap();
}