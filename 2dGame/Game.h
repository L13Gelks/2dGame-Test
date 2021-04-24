#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>  
#include <chrono>
#include "Player.h"
#include "Ground.h"
#include <vector>
#include <random>

class Game
{
public:
	Game();
	~Game();
	void WorldCreator();
	void startGame();
private:
	float worldDistance = 58500.0f;
	float traveledDistance = 0.0f;
	float worldTravelSpeed = 0.5f;
	float travelGroundCheckPoint = 0.0f;
	float travelGroundLastCheckPoint = 0.0f;
	int bottomGroundIndex = 0;
	std::vector<Ground> ground;
	static constexpr int screenHeight = 760;
	static constexpr int screenWidth = 1360;
};

