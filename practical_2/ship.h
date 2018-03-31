#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	// Default constructor is hidden
	Ship();

public:
	// Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	// Pure virtual deconstructor -- makes this an abstract class
	virtual ~Ship() = 0;
	// Update, virtual so can be orrided, but not pure virtual
	virtual void Update(const float &dt);
};