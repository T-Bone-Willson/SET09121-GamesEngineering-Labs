#pragma once

#include <ecm.h>
#include "cmp_actor_movement.h"

class EnemyAICom : public ActorMovementComponent {
protected:
	sf::Vector2f _direction;
	enum state { DEADEND, ROAMING, ROTATING, ROTATED }; // 4 States for Ghosts
	state _state;

public:
	explicit EnemyAICom(Entity* p);
	EnemyAICom() = delete;
	void render() override {}
	void update(float dt) override;
};