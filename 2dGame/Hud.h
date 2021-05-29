#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>   
#include <string>
#define MAX_NUMBER_STATS_DISPLAYED 4

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
	int HealhPoints = 0;
	int ManaPoints = 0;
	int StaminaPoints = 0;
	float radius = 50.0f;
	float MaxRadius = 50.0f;
	float Hbar = 300.0f;
	float Sbar = 200.0f;
	int exp = 0;
	sf::CircleShape inside;
	sf::CircleShape outline;
	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBorder;
	sf::RectangleShape spBar;
	sf::RectangleShape spBarBorder;
	sf::Vector2f pos;
	sf::Font font;
	sf::Text stats[MAX_NUMBER_STATS_DISPLAYED];
};