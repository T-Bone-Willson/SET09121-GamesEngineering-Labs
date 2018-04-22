#pragma once

//#include "entity.h"
#include <memory>
#include "ecm.h"
#include "system_renderer.h"

class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;
	virtual void update(float dt);
	virtual void render();
	virtual void load() = 0;
	std::vector<std::shared_ptr<Entity>> &getEnts();

protected:
	EntityManager _ents;
};