#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>
#include "main.h"

using namespace sf;
using namespace std;

// Things to remember about Box2D:
//     1. B2D has its own Vector maths classes that we munvert to/from.
//     2. B2D's positive y is towards the top of the screen.
//     3. B2D's has a scale. We render things in pixel.
//     4. Sam uses 1 unit = 1 meter when working on 3D games.
//     5. Box2D has a recommended 30 units per 1 pixel that feels realistic.

const int gameWidth = 1000;
const int gameHeight = 800;

b2World* world;
const float physics_scale = 30.f;
const float physics_scale_inv = 1 / physics_scale;
const int velocityIterations = 2;
const int positionIterations = 2;

vector<b2Body*>bodies;
vector<RectangleShape*> sprites;



// Conversion helper functions
// -------------------------------------------------------------------------------------------------

// Convert from b2Vec2 to Vector2f
inline const Vector2f bv2_to_sv2(const b2Vec2& in) {
	return Vector2f(in.x * physics_scale, (in.y * physics_scale));
}

// Convert from Vector2f to a b2Vec2
inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
	return b2Vec2(in.x * physics_scale_inv, (in.y * physics_scale_inv));
}

// Convert from Screenspace.y to physics.y
inline const Vector2f invert_height(const Vector2f& in) {
	return Vector2f(in.x, gameHeight - in.y);
}

// -------------------------------------------------------------------------------------------------

// Helper to add a body to the scene ---------------------------------------------------------------

// Create a Box3D body with a box fixture
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const Vector2f& position, const Vector2f size) {
	
	b2BodyDef BodyDef;
	// Is dynamic(Moving), or static(Stationary)

	BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
	BodyDef.position = sv2_to_bv2(position);

	// Create the body
	b2Body* body = world.CreateBody(&BodyDef);

	// Create the fixture shape
	b2PolygonShape Shape;
	Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
	b2FixtureDef FixtureDef;

	// Fixture properties
	FixtureDef.density = dynamic ? 10.f : 0.f;
	FixtureDef.friction = dynamic ? 0.8f : 1.f;
	FixtureDef.restitution = 1.0;
	FixtureDef.shape = &Shape;

	// Add to body
	body->CreateFixture(&FixtureDef);
	return body;
}

// Create a Box2d body with a box fixture, from a sfml::RectangleShape
b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs) {
	return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

// ---------------------------------------------------------------------------------------------

void init() {
	const b2Vec2 gravity(0.0f, 010.0f);

	// Construct a world, which holds and simulates the physics bodies
	world = new b2World(gravity);

	// Wall dimensions
	Vector2f walls[] = {
		// Top WALL position and size
		Vector2f(gameWidth * .5f, 5.f), Vector2f(gameWidth, 10.f),
		// Bottom WALL
		Vector2f(gameWidth * .5f, gameHeight - 5.f), Vector2f(gameWidth, 10.f),
		// Left WALL
		Vector2f(5.f, gameHeight * .5f), Vector2f(10.f, gameHeight),
		// Right WALL
		Vector2f(gameWidth - 5.f, gameHeight * .5f), Vector2f(10.f, gameHeight)
	};

	// Build WALLS!!!
	for (int i = 0; i < 7; i += 2) {

		// Create SFML shape for each wall
		auto s = new RectangleShape();
		s->setPosition(walls[i]);
		s->setSize(walls[i + 1]);
		s->setOrigin(Vector2f(walls[i + 1].x / 2, walls[i + 1].y / 2));
		s->setFillColor(Color::White);
		sprites.push_back(s);

		// Create a dynamic physics body for the box
		auto b = CreatePhysicsBox(*world, false, *s);
		bodies.push_back(b);
	}

	// Create Boxes
	for (int i = 1; i < 11; ++i) {
		// Create SFML shapes for each box
		auto s = new RectangleShape();
		s->setPosition(Vector2f(i * (gameWidth / 12.f), gameHeight * .7f));
		s->setSize(Vector2f(50.0f, 50.0f));
		s->setOrigin(Vector2f(25.0f, 15.0f));
		s->setFillColor(Color::White);
		sprites.push_back(s);

		// Create a dynamic physics body for the box
		auto b = CreatePhysicsBox(*world, true, *s);
		// Give the box a spin
		b->ApplyAngularImpulse(5.0f, true);
		bodies.push_back(b);
	}
}

// -----------------------------------------------------------------------------------------------------

void Update(RenderWindow &window) {

	// Resets clock, recalculates deltatime
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();

	// Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// Step Physics world by Dt (non-fixed timestep)
	world->Step(dt, velocityIterations, positionIterations);

	for (int i = 0; i < bodies.size(); ++i) {

		// Sync Sprites to physics position
		sprites[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));

		// Sync Sprites to physics rotation
		sprites[i]->setRotation((180 / b2_pi) * bodies[i]->GetAngle());
	}
}

void Render(RenderWindow &window) {
	for (auto s : sprites) window.draw(*s);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PHYSICS DAWG!");
	init();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
