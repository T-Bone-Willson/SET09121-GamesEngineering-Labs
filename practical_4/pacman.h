#pragma once

#include <SFML/Graphics.hpp>
#include "scene.h"

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;