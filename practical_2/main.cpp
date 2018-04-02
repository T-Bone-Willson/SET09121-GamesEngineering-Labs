#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"

using namespace sf;
using namespace std;

Texture spritesheet;
Sprite invader; // Possibly stop using this?

std::vector<Ship *> ships;
Ship* playerShip;

void Reset() {
	// Reset Invaders movement
	Invader::direction = true;
	Invader::speed = 30.f;
	Invader::speed = 160.f;
}

void Load() {
	// Load Spritesheet
	// If check for spritesheet load
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load srpitesheet!" << endl;
	}
	/*invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(0, 0, 32, 32));*/ // Will see if this needs to be removed?

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
	// Player
	auto player = new Player();
	playerShip = player;
	ships.push_back(player);

	Reset();
}

void Update(RenderWindow &window) {
	// Update Everything
	// Updates and resets clock. Adjust delta time as needed
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Event checking
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// Ships
	for (auto &s : ships) {
		s->Update(dt); // accessing data BEYOND the "pointer"
	}

	// Bullets
	Bullet::Update(dt);
}

void Render(RenderWindow &window) {
	// Draw window
	for (const auto &s : ships) {
		window.draw(*s);
	}
    Bullet::Render(window);
}

int Main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}