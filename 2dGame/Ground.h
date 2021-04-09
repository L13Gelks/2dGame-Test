#pragma once
#include <SFML/Graphics.hpp>
class Ground
{
public:
	Ground(const sf::Vector2f& pos, const sf::Vector2f& scaleFactor);
	void Draw(sf::RenderTarget& rt)const;
	void SetDirection();
	void Update(float dt);
	sf::Vector2f GetPosition();
	sf::FloatRect GetSize();
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f vel = { 0.0f, 0.0f };
	sf::Vector2f pos;
	sf::FloatRect size;
};

