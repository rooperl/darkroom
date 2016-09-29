#include "Game.h"

int main() {
	init();
	while (true) {
		setCursor();
		drawMap();
		if (map.light)
			std::cout << "You have turned the lights on." << fillTextBuffer();
		else
			std::cout <<"You're in a dark room." << fillTextBuffer();
		std::cout << "\n\nCoins: " << player.coins << fillTextBuffer() << "\n\n";
		wait(50);
		if (windowFocused()) checkKeyPresses();
		if (game.quit) return 0;
	}
}
