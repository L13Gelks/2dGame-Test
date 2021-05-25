#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include "Entity.h"

class TextureCodex2
{
public:
	static std::shared_ptr<sf::Texture> Acquire(const std::string& name);
	static void Clean();
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
};

class Enemy : public Entity
{
public:
	Enemy(int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor);
	Enemy(const Enemy& source);
	Enemy& operator=(const Enemy&) = delete;
	void Draw(sf::RenderTarget& rt)const;
	virtual void SetDirection();
	virtual void Update(float dt);
	sf::Vector2f GetPosition();
	sf::FloatRect GetSize();
	int getType();
	void setPosition(sf::Vector2f& newPos);
	void setTexture(std::string url);
	int enemyId = 0;
	float jumpForce = 0.0f;
	float speedForce = 0.0f;
	float rotateForce = 1.0f;
	virtual void rightCollision();
	virtual void leftCollision();
	std::shared_ptr<sf::Texture> pTexture;
protected:
	int type = 0;
	float degrees = 0;
	float jumpSpeed = 0.0f;

	sf::Sprite sprite;
	sf::Vector2f scaleFactor;
};

