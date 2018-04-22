#include "cmp_enemyAi.h"
#include "levelsystem.h"

using namespace sf;
using namespace std;

static const Vector2i directions[] = { { 1, 0 },{ 0, 1 },{ 0, -1},{ -1, 0} };

EnemyAICom::EnemyAICom(Entity* p) : _direction(directions[(rand() % 4)]), _state(ROAMING), ActorMovementComponent(p) {

}

void EnemyAICom::update(float dt) {
	// Movement
	
	// Amount to move
	const auto mva = (float)(dt * _speed);
	// Current position
	const Vector2f pos = _parent->getPosition();
	// Next position
	const Vector2f newpos = pos + _direction * mva;
	// Inverse of our current direction
	const Vector2i baddir = -1 * Vector2i(_direction);
	// Random new direction
	Vector2i newdir = directions[(rand() % 4)];

	switch (_state) {

	case ROAMING:
		if (ls::getTileAt(newpos) == ls::WALL) {
			_state = ROTATING;
		}
		else {
			move(_direction * mva);
		}
		break;

	case ROTATING:
		while (
			// Don't reverse
			newdir == baddir || ls::getTileAt(pos + (Vector2f(newdir) * 25.0f)) == ls::WALL) {
			// Pick new direction
			newdir = directions[rand() % 4];
		}
		_direction = Vector2f(newdir);
		_state = ROTATED;
		break;
		
	case ROTATED:
		// Have we left the waypoint?
		if (ls::getTileAt(pos) != ls::WAYPOINT) {
			_state = ROAMING; // YES
		}
		move(_direction * mva); // NO
		break;

	case DEADEND:
		break;

	default:
		break;
	}

	ActorMovementComponent::update(dt);
}