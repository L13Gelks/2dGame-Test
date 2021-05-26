#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Player.h"
#define MAX_NUMBER_OPTIONS 3
#define MAX_NUMBER_STATS 8

class Menu
{
public:
	Menu(int width, int height);
	void draw(sf::RenderTarget& rt);
	int getOption();
	void showStats(sf::RenderTarget& rt, Player& player);
	void MoveUp();
	void MoveDown();
	void setPosition(sf::Vector2f& pos);
private: 
	int screenHeight = 760;
	int screenWidth = 1360;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f pos;
	int selectedItem;
	sf::Font font;
	sf::Text text[MAX_NUMBER_OPTIONS];
	sf::Text stats[MAX_NUMBER_STATS];
};

