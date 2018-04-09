#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"
#include "player.h"
#include "ghost.h"
#include "system_renderer.h"
#include "pacman.h"
#include "scene.h"

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
	shared_ptr<Entity> player = make_shared<Player>(); // Adds the player entity the the EntityManager
	em.list.push_back(player);
	// "make_shared<player>();" calls the constructor of player with no parameters

	// Ghosts
	for (int i = 0; i < 4; i++) {
		shared_ptr<Entity> ghost = make_shared<Ghost>()); // Adds the Ghost entity into the EntityManager
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
		em.update(dt);	
}

void Render(RenderWindow &window) {
		em.render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PACMAN");
	Renderer::initialise(window); // This ties to the system_renderer!!!!
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
