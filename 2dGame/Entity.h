#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
    Entity();
    sf::Vector2f pos;
    sf::FloatRect size;
    sf::Vector2f vel = { 0.0f, 0.0f };
    float speed = 0.0f;
    bool validJump = false;
    bool falling = true;
    float mass = 0.0f;
protected:

};

