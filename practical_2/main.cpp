#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"



using namespace sf;
using namespace std;

Texture spritesheet;
Sprite invader;

std::vector<Ship *> ships;


void Load() {
	// Load Spritesheet
	// If check for spritesheet load
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load srpitesheet!" << endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(0, 0, 32, 32));

	// Load Invader
	Invader* inv = new Invader(sf::IntRect(0, 0, 32, 32), { 100, 100 });
	ships.push_back(inv);

	for (int r = 0; r < invaders_rows; ++r) {
		// IntRect points to "Left, Top, Width, Height" on the spritesheet
		auto rect = IntRect(32 * r, 0, 32, 32);

		for (int c = 0; c < invaders_columns; ++c) {
			float leftMargin = gameWidth / 2 - 32 * invaders_columns / 2; // sets value for this variable
			float topMargin = 64.f; // sets value for this variable.
			Vector2f position = { leftMargin + 32.f * c, topMargin + 32.f * r };
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
}

void Update(double dt) {
	// Update Everything
	static Clock clock;
	float dt = clock.restart().asSeconds();

	// Ships
	for (auto &s : ships) {
		s->Update(dt); // accessing data BEYOND the "pointer"
	};
}

void Render(RenderWindow &window) {
	// Draw window
	for (const auto &s : ships) {
		window.draw(*s);
	}
}

int Main() {
	// Initialise and Load
	//while() {
		// Calculate DT
		//Update(dt);
		//Render();
		// Wait for Vsync
	//}
	// Unload and shutdown
}