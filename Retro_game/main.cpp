#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

/*
Vector2f moveTriangle(uint8_t keyCombined, float dt) {

	// return Vector2f XYPos;
}
*/
int main()
{
	Color color;
	const float PI = 3.14159265358979323846;
	cout << fixed;
	// Window
	const unsigned int vWidth = 800;
	const unsigned int vHeight = 600;
	RenderWindow window(VideoMode(vWidth, vHeight), "Game");
	window.setFramerateLimit(144);
	// window.setVerticalSyncEnabled(1);
	// Do a settings menu just for UI practise

	// Sprite data
	Vector2f triPosition(vWidth / 2.f, vHeight / 2.f);
	float triSpeed = 2.f;
	// 
	Vector2f triVelocity(0.f, 0.f);
	float rotationSpeed = 200.f;
	float triAngle = 0.f;
	// float triVelocity = 0.f;
	float xDirection = 0.f;
	float yDirection = 0.f;
	// Sprite gfx
	const unsigned int spriteWidth = 64;
	const unsigned int spriteHeight = 64;
	// Texture
	Texture texture;
	if (!texture.loadFromFile("sprites/SpriteTriangle.png", IntRect(0, 0, spriteWidth, spriteHeight))) {
		// Error
	}
	texture.setSmooth(1);
	Sprite triangleSprite;
	triangleSprite.setTexture(texture);
	triangleSprite.setTextureRect(IntRect(64, 0, -64, spriteHeight));	// Drawn in reverse
	triangleSprite.setOrigin(32.5f, 32.5f);
	triangleSprite.setPosition(triPosition);
	// Due to scope stuff
	uint8_t keyCombination = 0x00;
	// Start clock
	Clock clock;
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				keyCombination = 0x00;
				if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
					keyCombination |= 1 << 3;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
					keyCombination |= 1 << 2;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
					keyCombination |= 1 << 1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
					keyCombination |= 1 << 0;
				}
				break;
			case Event::KeyReleased:
				if (!Keyboard::isKeyPressed(Keyboard::Key::W)) {
					keyCombination &= ~(1 << 3);
				}
				if (!Keyboard::isKeyPressed(Keyboard::Key::S)) {
					keyCombination &= ~(1 << 2);
				}
				if (!Keyboard::isKeyPressed(Keyboard::Key::A)) {
					keyCombination &= ~(1 << 1);
				}
				if (!Keyboard::isKeyPressed(Keyboard::Key::D)) {
					keyCombination &= ~(1 << 0);
				}
				break;
			default:
				break;
			}
		}
		// Make a bool for each key instead
		// x/y direction and THEN apply speed in that direction?
		// New position - old position is vector 

		// Rotate with A and D then apply speed with W and S

		// Double check origin and centers, slightly off center but could be due to sprite

		// 
		if (keyCombination & (1 << 1)) {
			// xDirection -= 1.f * triSpeed * deltaTime;
			triAngle -= 1.f * rotationSpeed * deltaTime;
			if (triAngle < 0.f) {
				triAngle = 360.f;
			}
		}
		if (keyCombination & (1 << 0)) {
			// xDirection += 1.f * triSpeed * deltaTime;
			triAngle += 1.f * rotationSpeed * deltaTime;
			if (triAngle > 360.f) {
				triAngle = 0.f;
			}
		}

		xDirection = cos(triAngle * PI / 180);
		yDirection = sin(triAngle * PI / 180);
		cout << "x" << xDirection << endl;
		cout << "y" << yDirection << endl;

		if (keyCombination & (1 << 3)) {
			// yDirection -= 1.f * triSpeed * deltaTime;
			triVelocity.x += xDirection * triSpeed * deltaTime;
			triVelocity.y += yDirection * triSpeed * deltaTime;
		}
		if (keyCombination & (1 << 2)) {
			// yDirection += 1.f * triSpeed * deltaTime;
			triVelocity.x -= xDirection * triSpeed * deltaTime;
			triVelocity.y -= yDirection * triSpeed * deltaTime;
		}

		if (triPosition.x > vWidth) {
			triPosition.x = 0.f;
		}
		else if (triPosition.x < 0.f) {
			triPosition.x = 800.f;
		}
		else if (triPosition.y > vHeight) {
			triPosition.y = 0.f;
		}
		else if (triPosition.y < 0.f) {
			triPosition.y = 600.f;
		}

		// triPosition += {xDirection, yDirection};
		triPosition += triVelocity;
		// triangleSprite.move(xDirection, yDirection);
		// triangleSprite.move(triVelocity);
		triangleSprite.setPosition(triPosition);
		// triangleSprite.setRotation(atan2(yDirection, xDirection) * 180 / PI);
		triangleSprite.setRotation(triAngle); // * 360

		// cout << triAngle << endl;

		// cout << atan2(1.f, 1.f) * 180 / PI << endl;
		// cout << triangleSprite.getRotation() << endl;
		// cout << (atan2(yDirection, xDirection) * 180 / PI) << endl;

		window.clear();
		window.draw(triangleSprite);
		window.display();

	}

	return 0;
}