#pragma once

#include <SFML/Graphics.hpp>
#include "scene.h"
#include "ecm.h"

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 1000;

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene { // This is the scene for the menu
private:
	sf::Text text;

public:
	MenuScene() = default;
	void update(float dt) override;
	void render() override;
	void load() override;
};

class GameScene : public Scene { // Game scene like pacman, ghosts and shit
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	GameScene() = default;
	void update(float dt) override;
	void render()override;
	void load()override;
};