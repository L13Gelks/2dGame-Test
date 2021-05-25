#pragma once
#include "Enemy.h"

class PelotaMiedo : public Enemy
{
public:
	PelotaMiedo(int id, int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor);
	void rightCollision() override;
	void leftCollision() override;
private:
};

