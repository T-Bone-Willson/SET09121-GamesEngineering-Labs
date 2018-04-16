#include "pacman.h"
//#include "entity.h"
//#include "player.h"
//#include "ghost.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_player_movement.h"
#include "cmp_enemyAi.h"
#include "levelsystem.h"

#define GHOST_COUNT 4

using namespace std;
using namespace sf;

shared_ptr<Entity> player;
vector<shared_ptr<Entity>> ghosts;

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
	
}

void GameScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	ls::render(Renderer::getWindow()); // MAKE A NOTE OF THIS!!!
	Scene::render();
}

void GameScene::respawn() {
	//Copied from load()
	//pl->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghosts) {
		g->setPosition(ls::getTilePosition(ghost_spawns[rand() % GHOST_COUNT]));
	}
}

void GameScene::load() {

	ls::loadLevelFile("res/pacman.txt", 25.f);

	{
		player = make_shared<Entity>();

		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		player->addComponent<PlayerMovementComponent>(); // Comes from Player movement component

		//May need to move/copy to respawn()
		//pl->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

		_ents.list.push_back(player);
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
		ghost->addComponent<EnemyAICom>();
		//ghost->setPosition({ 300.f, 300.f });

	_ents.list.push_back(ghost);
	ghosts.push_back(ghost);
	}
	
	respawn();
}