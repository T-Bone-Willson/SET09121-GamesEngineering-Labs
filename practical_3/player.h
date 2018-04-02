#pragma once

#include "entity.h"
// Creating entity "Player"
class Player : public Entity { // Standard implementations for creating an Entity.
private:
	float _speed;

public:
	void update(double dt) override;
	Player();
	void render(sf::RenderWindow &window) const override;
};