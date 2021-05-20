#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

class TextureCodex2
{
public:
	static std::shared_ptr<sf::Texture> Acquire(const std::string& name);
	static void Clean();
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
};

class Enemy
{
public:
	Enemy(int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor);
	Enemy(const Enemy& source);
	Enemy& operator=(const Enemy&) = delete;
	void Draw(sf::RenderTarget& rt)const;
	void SetDirection();
	void Update(float dt);
	sf::Vector2f GetPosition();
	sf::FloatRect GetSize();
	int getType();
private:
	int type = 0;
	int degrees = 0;
	std::shared_ptr<sf::Texture> pTexture;
	sf::Sprite sprite;
	sf::Vector2f vel = { 0.0f, 0.0f };
	sf::Vector2f pos;
	sf::Vector2f scaleFactor;
	sf::FloatRect size;
};

