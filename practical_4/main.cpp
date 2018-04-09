#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "entity.h"
#include "player.h"
#include "ghost.h"

using namespace sf;
using namespace std;


// Think I need to remove this for my EntityManager systems...
/*std::vector<Entity *> entities;
Player* player;*/

EntityManager em; // All entities parse or go through here... I think

void Reset() {
	//player->setPosition({ 50.f, 50.f });
}

void Load() {

	// Player
	//player = new Player();
	//entities.push_back(player);

	shared_ptr<Entity> player = make_shared<Entity>(Player()); // Adds the player entity the the EntityManager
	em.list.push_back(player);

	// Ghosts
	for (int i = 0; i < 4; i++) {
		//Ghost* ghost = new Ghost();
		//entities.push_back(ghost);

		shared_ptr<Entity> ghost = make_shared<Entity>(Ghost()); // Adds the Ghost entity into the EntityManager
		em.list.push_back(ghost);
	}
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

	//for (auto &e : entities) {
		e->update(dt);
	//}
}

void Render(RenderWindow &window) {
	//for (auto &e : entities) {
		e->render(window);
	//}
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
