#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"

using namespace sf;
using namespace std;

void Reset() {

}

void Load() {
	Reset();
}

void Update(RenderWindow &window) {
	// reset Clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consumer events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow &window) {

}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PACMAN");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
