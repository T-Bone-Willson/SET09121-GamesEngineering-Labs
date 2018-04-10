#include <SFML/Graphics.hpp>
#include <iostream>
#include "entity.h"
#include "system_renderer.h"
#include "pacman.h"
#include "scene.h"

using namespace sf;
using namespace std;


// Think I need to remove this for my EntityManager systems...
/*std::vector<Entity *> entities;
Player* player;*/

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

void Load() {
	// Load Scene assets that correspond to the scene...
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	// start at main menu
	activeScene = menuScene;
}
void Update(RenderWindow &window) {
	// reset Clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->update(dt);
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
	activeScene->render();
	// Flush to screen
	Renderer::render();
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
