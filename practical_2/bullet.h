#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
	// Update ALL bullets
	static void Update(const float &dt);

	// constructor
	Bullet(const sf::Vector2f &pos, const bool mode);

	// Render ALL bullets
	static void Render(sf::RenderWindow &window);

	// Choose and inactive bullet and use it
	static void Fire(const sf::Vector2f &pos, const bool mode);

	~Bullet() = default;

protected:
	// false = player bullet, true = Enemy bullet
	bool _mode;

	// "bulletPointer" is a pointer for the next bullet spawn
	// there are 255 bullets to use and then it wraps around back to 0 again where it's replenished... I think...
	static unsigned char bulletPointer;
	static Bullet bullets[256];

	Bullet(); // Do'nt think we use this?

	// Called by Static update
	void _Update(const float &dt);
};