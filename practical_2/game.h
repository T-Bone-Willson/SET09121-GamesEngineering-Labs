#pragma once
#include <SFML/Graphics.hpp>
#include "ship.h"

// sets varibles below as "constant"
constexpr uint16_t gameWidth = 800; // sets width of gamw windo
constexpr uint16_t gameHeight = 600; // sets height of game window
constexpr uint16_t invaders_rows = 5; // sets number or rows for invaders
constexpr uint16_t invaders_columns = 12; // sets number of columns for invaders

extern sf::Texture spritesheet;
extern std::vector<Ship *> ships;
extern Ship* playerShip;