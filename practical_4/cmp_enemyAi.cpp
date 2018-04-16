#include "cmp_enemyAi.h"

using namespace sf;
using namespace std;

EnemyAICom::EnemyAICom(Entity* p) : ActorMovementComponent(p) {

}

void EnemyAICom::update(float dt) {
	// Movement
	
	sf::Vector2f displacement = { 0.0f, 0.0f };
	
	displacement.x = rand() % 2 + 0 - 1;
	displacement.y = rand() % 2 + 0 - 1;

	// Normalised displacement
	float l = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	if (l != 0) {
		displacement.x = displacement.x / 1;
		displacement.y = displacement.y / 1;
	}

	move((float)dt * displacement * _speed); // direction for player.
	
}