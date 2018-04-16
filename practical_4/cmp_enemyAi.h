#pragma once

#include <ecm.h>
#include "cmp_actor_movement.h"

class EnemyAICom : public ActorMovementComponent {

public:
	explicit EnemyAICom(Entity* p);
	EnemyAICom() = delete;
	void render() override {}
	void update(float dt) override;
};