#pragma once
#include <SFML/Graphics.hpp>
// Variables underneath are set as "Constant"
constexpr uint16_t gameWidth = 800; // Sets width of game
constexpr uint16_t gameHeight = 600; // Sets height of game
constexpr uint16_t invaders_rows = 5; // Sets size of invader rows
constexpr uint16_t invaders_columns = 12; // sets size of invader rows

// Makes "spritesheet" external so "Ship.cpp" can access it. if "game.h" is #include
extern sf::Texture spritesheet;