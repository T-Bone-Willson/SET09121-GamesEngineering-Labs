#include "pacman.h"
//#include "entity.h"
#include "player.h"
#include "ghost.h"
#include "entity.h"
#include "cmp_sprite.h"

#define GHOST_COUNT 4

using namespace std;
using namespace sf;

void MenuScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
}

void MenuScene::render() {
	Scene::render();
}

void MenuScene::load() {
	// Title Text

	/*
	Font font;
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString("One Day I'll Finish Pacman");
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
	*/
}

void GameScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	Scene::render();
}

void GameScene::respawn() {

}

void GameScene::load() {

	// Player
	/*
	shared_ptr<Entity> player = make_shared<Player>();
	// This ^^^ calls the constructor of the Player with no parameters

	_ents.list.push_back(player);

	player->setPosition({ 30.0f, 30.0f });
	*/
	{
		auto pl = make_shared<Entity>();

		auto s = pl->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(pl);
	}

	const sf::Color ghost_cols[]{
		{208, 62, 25},	// red Blinky
		{219, 133, 28},	// orange Clyde
		{70, 191, 238}, // cyan Inky
		{234, 130, 229} // pink Pinky
	};

	for (int i = 0; i < GHOST_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

	// Ghosts
	_ents.list.push_back(ghost);
	}
}