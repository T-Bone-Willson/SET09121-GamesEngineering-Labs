#include <SFML/Graphics.hpp>

// Below is main.cpp code, it's commented out because... reasons
/*int main(){
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed){
		  window.close();
		}
	}
	window.clear();
	window.draw(shape);
	window.display();
  }
  return 0;
}*/
// Above is main.cpp code

using namespace sf;
using namespace std;

// Controls for Player 1 and 2 on keyboard.
const Keyboard::Key controls[4] = { // control [4] is a defined size array!
	Keyboard::A,	//Player 1 Up
	Keyboard::Z,	//Player 1 Down
	Keyboard::Up,	//Player 2 Up
	Keyboard::Down	//Player 2 Down
};

// Width and Height of player 1 & 2 paddles.
const Vector2f paddleSize(25.f, 100.f);
// Size of PONG ball
const float ballRadius = 10.f;
// Creates width of game board
const int gameWidth = 800;
// Creates height of game board
const int gameHeight = 600;
// Default speed of paddle
const float paddleSpeed = 400.f;
// Velolcity for the ball using a Vector2f data type. Speed + Direction.
Vector2f ballVelocity;
// decides which way the ball is moving at the start of a game.
bool server = false;

// Define shape of PONG ball
CircleShape ball;
// Define shape of PONG paddle + creates 2 of them!
RectangleShape paddles[2];

void Load() {
	// Set size and origin of paddles
	for (auto &p : paddles) {
		// Ask Sam about this logic. Why define paddleSize size previously
		// then subtract both Width and Height by 3.f here?...
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3); // Again, why define radius previously then subtract by 3 here?...
	ball.setOrigin(ballRadius / 2, ballRadius / 2); // Ask same about the mathemtaical logic here!...

	
	// I CAN MAYBE DELETE THIS SEGMENT OF COMMENTED CODE!!!
	/*
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(770 + paddleSize.x / 2, gameHeight / 2); //Check with Sam if this is correct!!!
	// reset Ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2); //May not work...
	*/
	
	// Inline IF Statement, "If the statement befoe the ? is true, then ballVelocity.x is set to -100.0f, 
	// if server is false ballVelocity.x = 60.0f"
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}

void Reset() {
	// reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(770 + paddleSize.x / 2, gameHeight / 2); //Check with Sam if this is correct!!!
	// reset Ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2); //May not work... IT WORKS!!!
}

void Update(RenderWindow &window) {
	// Reset clock, recalculate deltatime (dt)
	static Clock clock;
	float dt = clock.restart().asSeconds(); //dt should be approximately 16ms (1/60)
	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Quit via the ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// Handle paddle movement
	// IF CONTROLING/MOVING BOTH AT THE SAME TIME, RIGHT PADDLE WILL GO FASTER!!!! DUNKT KNOW WHY, ASK SAM!!!
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--; // Paddle goes down vertically
		// Add relevant paddle (Left) to desired controls
		paddles[0].move(0, direction * paddleSpeed * dt);
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++; // Paddle goes up vertically
		paddles[0].move(0, direction * paddleSpeed * dt);
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		direction--; // Paddle goes down vertically
		// Add relevant paddle (Right) to desired controls
		paddles[1].move(0, direction * paddleSpeed * dt);
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		direction++; // Paddle goes up vertically
		paddles[1].move(0, direction * paddleSpeed * dt);
	}

	// Move ball by it's velocity in correspondence to Delta Time
	ball.move(ballVelocity * dt);

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) {
		// Bottom Wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	else if (by < 0) {
		// Top Wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth){
		// Right Wall
		Reset();
	}
	else if (bx < 0) {
		// Left Wall
		Reset();
	}
	else if (
		// Ball is inline or behind paddle
		bx < paddleSize.x 
		&& // AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5)
		&& // AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
		) {
		// Bounce off left paddle
		// I swaped the -1.1f on the .y to the .x. This means it's now calculutlating a collision/rebound on it's x Axis rather than it's y axis
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(0, -10);
	}
	else if (
		bx < paddleSize.x
		&&
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5)
		&&
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
		) {
		// Bounce off right paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(0, 10);
	}
	//paddles[0].move(0, direction * paddleSpeed * dt);
	//paddles[1].move(0, direction * paddleSpeed * dt);
}

void Render(RenderWindow &window) {
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}