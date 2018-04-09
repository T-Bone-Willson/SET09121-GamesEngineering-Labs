#include "ghost.h"
#include "system_renderer.h"

using namespace sf;
using namespace std;

void Ghost::update(float dt) {
	// Movement

	Entity::update(dt);
}

Ghost::Ghost() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Blue);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Ghost::render(sf::RenderWindow &window) const {
	Renderer::queue(_shape.get());
}