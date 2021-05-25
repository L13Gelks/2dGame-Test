#include "PelotaMiedo.h"

PelotaMiedo::PelotaMiedo(int id,int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor)
	:
Enemy(type, pos, scaleFactor)
{
	setTexture("sprite/ball.png");
	speed = 100.0f;
	vel = { 1.0f, 1.0f };
	enemyId = id;
	speedForce = 2;
	rotateForce = 4;
	jumpForce = 300;
}

void PelotaMiedo::rightCollision() 
{
	validJump = false;
	falling = true;
	speedForce = -speedForce;
	speedForce *= 0.9f;
	rotateForce = -rotateForce;
	rotateForce *= 0.9f;
}

void PelotaMiedo::leftCollision()
{
	validJump = false;
	falling = true;
	speedForce = -speedForce;
	speedForce *= 0.9f;
	rotateForce = -rotateForce;
	rotateForce *= 0.9f;
}

