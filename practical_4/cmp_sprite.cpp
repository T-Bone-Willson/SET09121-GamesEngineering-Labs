#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;
using namespace sf;

// I don't know why this (below) was giving red errors... It's straight from the workbook

/*void SpriteComponent::update(float dt) {
	_sprite->setPosition(_parent->getPosition());
}*/ 

void ShapeComponent::render() {
	Renderer::queue(_shape.get());
}

sf::Shape& ShapeComponent::getShape() const { 
	return *_shape; 
}

ShapeComponent::ShapeComponent(Entity* p) : Component(p), _shape(make_shared<sf::CircleShape>()) {

}