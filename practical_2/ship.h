#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected: // Private and protected. Can't be changed
	sf::IntRect _sprite;
	// Default Constructor is hidden
	Ship();

public: // public and can be changed
	// Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	// Pure virtual deconstructor, makes this an abstract class
	virtual ~Ship() = 0;
	// Update, virtual so can be orrerided, but not pure virtual
	virtual void Update(const float &dt); // Adds delta time
};

class Invader : public Ship {
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float &dt) override;
	static bool direction; // all invader sprites move as one
	static float speed; // all invader sprites have same speed
};