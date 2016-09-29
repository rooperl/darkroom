#include "DarkRoom.h"

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
