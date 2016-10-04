#include <iostream>
#include <string>
#include "Game.h"
#include "Map.h"

Game game;
Player player;
Map map;

int main() {
	init(player, map);
	while (!game.quit) {
		setCursor();
		drawMap(player, map);
		if (map.light) std::cout << "You have turned the lights on." << fillTextBuffer();
		else std::cout <<"You're in a dark room." << fillTextBuffer();
		std::cout << "\n\nCoins: " << player.coins << fillTextBuffer() << "\n\n";
		wait(GAME_SPEED);
		if (windowFocused()) checkKeyPresses(game, map, player);
	}
	return 0;
}
