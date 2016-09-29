#include "DarkRoom.h"
#include <chrono>
#include <thread>

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
	resetMap();
}

bool windowFocused() {
	return GetConsoleWindow() == GetForegroundWindow();
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
		if (game.quit) return 0;
	}
}