#include <SFML/Graphics.hpp>
#include <iostream>
#include "LevelSystem.h"
#include "player.h"
#include "entity.h"
#include "game.h"

using namespace sf;
using namespace std;

std::vector<Entity *> entities;
Player* player;

void Reset() {

}

void Load() {
	// Player
	player = new Player();
	entities.push_back(player);

	// Level
	ls::loadLevelFile("res/maze_2.txt");

	// Print level to the console
	cout << "|| PRINTING LEVEL ||" << endl;
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}
	cout << "\\\\\\\\\\//////////" << endl;

	Reset();
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check and consume events
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

	for (auto &e : entities) {
		e->update(dt);
	}
}

void Render(RenderWindow &window) {
	ls::render(window);
	for (auto &e : entities) {
		e->render(window);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Tile Engine");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}