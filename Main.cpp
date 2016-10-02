#include <iostream>
#include <string>

#include "Game.h"
#include "Map.h"

Map map;
Player player;
Game game;

int main() {
	init(player, map);
	while (true) {
		setCursor();
		drawMap(player, map);
		if (map.light) std::cout << "You have turned the lights on." << fillTextBuffer();
		else std::cout <<"You're in a dark room." << fillTextBuffer();
		std::cout << "\n\nCoins: " << player.coins << fillTextBuffer() << "\n\n";
		wait(50);
		if (windowFocused()) checkKeyPresses(game, map, player);
		if (game.quit) return 0;
	}
}
