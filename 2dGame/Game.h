#pragma once


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>  
#include <chrono>
#include "Player.h"

class Game
{
public:
	Game();
	void startGame();
private:
	static constexpr int screenHeight = 1360;
	static constexpr int screenWidth = 760;
};

