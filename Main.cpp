<<<<<<< HEAD
#include <iostream>
#include <string>
#include "Game.h"
#include "Map.h"

Player player;
Map map;

int main() {
	init(player, map);
	while (!map.quit) {
		setCursor();
		drawMap(player, map);
		if (map.light) std::cout << "You have turned the lights on." << fillTextBuffer();
		else std::cout <<"You're in a dark room." << fillTextBuffer();
		std::cout << "\n\nCoins: " << player.coins << fillTextBuffer() << "\n\n";
		wait(GAME_SPEED);
		if (windowFocused()) checkKeyPresses(map, player);
	}
	return 0;
}
=======
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
>>>>>>> 670d61cc465dd8818df27b98dc19b6bdb4ec15cf
