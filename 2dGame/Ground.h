#pragma once
#include <SFML/Graphics.hpp>
class Ground
{
public:
	Ground(int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor);
	Ground(const Ground& source);
	void Draw(sf::RenderTarget& rt)const;
	void SetDirection();
	void Update(float dt);
	sf::Vector2f GetPosition();
	sf::FloatRect GetSize();
	int getType();
private:
    enum class GroundType
    {
		Ground,
		Water,
		Background
    };
private:
	int type = 0;
	float groundFlowTime = 0.0f;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f vel = { 0.0f, 0.0f };
	sf::Vector2f pos;
	sf::Vector2f scaleFactor;
	sf::FloatRect size;
};

