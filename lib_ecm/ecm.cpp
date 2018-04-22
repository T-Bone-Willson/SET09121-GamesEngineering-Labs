#include "ecm.h"

using namespace std;
using namespace sf;

Entity::Entity() : _position({ 0, 0 }), _rotation(0), _alive(true), _visible(true), _fordeletion(false) {

}

const sf::Vector2f & Entity::getPosition()const {
	return _position;
}

void Entity::setPosition(const Vector2f &pos) { 
	Entity::_position = pos; 
}

void Entity::update(const float dt) {
	for (auto c : _components) {
		c->update(dt);
	}
}

bool Entity::is_fordeletion() const { return _fordeletion; }

void Entity::render() {
	for (auto c : _components) {
		c->render();
	}
}

float Entity::getRotation() const { return _rotation; }
void Entity::setRotation(float _rotation) { Entity::_rotation = _rotation; }
bool Entity::isAlive() const { return _alive; }
void Entity::setAlive(bool _alive) { Entity::_alive = _alive; }

void Entity::setForDelete() {
	_fordeletion = true;
	_alive = false;
	_visible = false;
}

bool Entity::isVisible() const { return _visible; }
void Entity::setVisible(bool _visible) { Entity::_visible = _visible; }

Component::Component(Entity * const p) : _parent(p), _fordeletion(false) {

}

Entity::~Entity() {
	// Component may need tried deleted ttime and time again until they are gone. This is due to reasons... 

	int deli = 0;
	while (deli != _components.size()) {
		deli = _components.size();
		_components.erase(
			remove_if(_components.begin(), _components.end(), [](auto& sp) {return (sp.use_count() <= 1); }),
			_components.end());
	}

	if (_components.size() > 0) {
		throw std::runtime_error("OHH MY GAWD!!! CAN'T DELETE ENTITY!!! It's being GRABED!!!");
	}

	_components.clear();
}

Component::~Component() {}

bool Component::is_fordeletion() const { return _fordeletion; }

void EntityManager::update(float dt) {
	for (size_t i = 0; i < list.size(); i++) {
		if (list[i]->is_fordeletion()) {
			list.erase(list.begin() + i);
			--i;
			continue;
		}
		if (list[i]->isAlive()) {
			list[i]->update(dt);
		}
	}
}

void EntityManager::render() {
	for (auto& e : list) {
		if (e->isVisible()) {
			e->render();
		}
	}
}