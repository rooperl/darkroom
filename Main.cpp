#include "Game.h"

int main() {
	init();
	while (true) {
		fillTextBuffer(5);
		clearScreen();
		drawMap();
		if (map.light)
			std::cout << "You have turned the lights on.";
		else
			std::cout << "You're in a dark room.";
		std::cout << "\n\nCoins: " << player.coins << "\n\n";
		wait(50);
		if (windowFocused()) checkKeyPresses();
		if (game.quit) return 0;
	}
}
