#pragma once
#include "Player.h"
#include "Map.h"

const short GAME_SPEED = 50;
const std::string FILENAME = "darkroom.drmp";
const std::string MANUAL_EDIT_TEXT = "MANUAL_EDIT";

void wait(short milliseconds);
void init(Player& player, Map& map);
void setCursor(short y = 0, short x = 0);
std::string fillTextBuffer();
bool windowFocused();
bool toggleKey(short VK);
void readFile(Map& map, Player& player);
void writeFile(Map map);
void checkKeyPresses(Map& map, Player& player);
