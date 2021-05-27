#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>  
#include <chrono>
#include "Player.h"
#include "Ground.h"
#include "Enemy.h"
#include "PelotaMiedo.h"
#include "Slime.h"
#include "Menu.h"
#include "Hud.h"
#include <vector>
#include <random>

class Game
{
public:
	Game();
	~Game();
	void WorldCreator();
	void startGame();
	int TestCollision(const sf::FloatRect& obj_size1, const sf::Vector2f& obj_pos1, 
		const sf::FloatRect& obj_size2, const sf::Vector2f& obj_pos2);
	void checkButton(sf::RenderTarget& rt);
private:
	void PlayerInput(Player& player);
	void enemyPhysics(Player& player, sf::RenderTarget& rt);
private:
	bool menuPressed = false;
	float dt = 0.0f;
	sf::Text text;
	float worldDistance = 58500.0f;
	float traveledDistance = 0.0f;
	float worldTravelSpeed = 0.5f;
	float playerPosX = 0.0f;
	float playerLastPosX = 0.0f;
	float playerMoveX = 0.0f;
	float travelGroundCheckPoint = 0.0f;
	float travelGroundLastCheckPoint = 0.0f;
	int bottomGroundIndex = 0;
	std::vector<Ground> ground;
	std::vector<Enemy*> enemy;
	static constexpr int screenHeight = 760;
	static constexpr int screenWidth = 1360;
};

