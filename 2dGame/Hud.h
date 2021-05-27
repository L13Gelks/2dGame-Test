#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Player.h"
#define MAX_NUMBER_STATS 2

class Hud
{
public:
	Hud(int width, int height);
	void draw(sf::RenderTarget& rt);
	void setStats(Player& player);
	void setPosition(sf::Vector2f& pos);
private:
	int screenHeight = 760;
	int screenWidth = 1360;
	float radius = 50.0f;
	float MaxRadius = 50.0f;
	float Hbar = 300.0f;
	float Sbar = 200.0f;
	sf::CircleShape inside;
	sf::CircleShape outline;
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBorder;
	sf::RectangleShape spBar;
	sf::RectangleShape spBarBorder;
	sf::Vector2f pos;
	sf::Font font;
	sf::Text stats[MAX_NUMBER_STATS];
};