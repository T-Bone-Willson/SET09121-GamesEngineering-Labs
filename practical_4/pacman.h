#pragma once

#include <SFML/Graphics.hpp>
#include "scene.h"

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene { // This is the scene for the menu
private:
	sf::Text text;

public:
	MenuScene();
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