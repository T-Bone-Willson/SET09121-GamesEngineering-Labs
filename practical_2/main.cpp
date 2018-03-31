#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Texture spritesheet;
Sprite invader;

void Load() {
	// If check for spritesheet load
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load srpitesheet!" << endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(0, 0, 32, 32));
}

void Update(double dt) {
	// Update Everything
	static sf::Clock clock;
	//const float dt = clock.restart()asSeconds();
}

void Render() {
	// Draw Everything
	window.draw(invader); //unsure why "window" is undefined

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