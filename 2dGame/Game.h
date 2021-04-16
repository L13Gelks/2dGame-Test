#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>  
#include <chrono>
#include "Player.h"
#include "Ground.h"

class Game
{
public:
	Game();
	~Game();
	void startGame();
private:
	static constexpr int screenHeight = 760;
	static constexpr int screenWidth = 1360;
};

