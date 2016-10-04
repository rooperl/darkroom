#pragma once
#include "Player.h"
#include "Map.h"

#define GAME_SPEED 50
#define FILENAME "darkroom.drmp"
#define MANUAL_EDIT_TEXT "MANUAL_EDIT"

class Game {
public:
	bool quit;
};

void wait(int milliseconds);
void init(Player& player, Map& map);
void setCursor(short y = 0, short x = 0);
std::string fillTextBuffer();
bool windowFocused();
bool toggleKey(short VK);
void readFile(Map& map, Player& player);
void writeFile(Map map);
void checkKeyPresses(Game& game, Map& map, Player& player);
