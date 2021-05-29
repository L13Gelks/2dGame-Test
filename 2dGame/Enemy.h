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
public:
	void setExperiencePoints(float exp);
	float getExperiencePoints();
	void setDamage(float dmg);
	//Stats
	void setHealthPoints(float hp);
	float getHealthPoints();
	void setMaxHealthPoints(float mhp);
	float getMaxHealthPoints();
	void setHealthPointsRegen(float hpr);
	float getHealthPointsRegen();
	void setStaminaPoints(float sp);
	float getStaminaPoints();
	void setMaxStaminaPoints(float msp);
	float getMaxStaminaPoints();
	void setStaminaPointsRegen(float spr);
	float getStaminaPointsRegen();
	void setManaPoints(float mp);
	float getManaPoints();
	void setMaxManaPoints(float mmp);
	float getMaxManaPoints();
	void setManaPointsRegen(float mpr);
	float getManaPointsRegen();
protected:
	float Experience = 0.0f;
	float immunityCooldown = 0.0f;
	bool immunity = false;
	float HealthPoints = 50.0f;
	float MaxHealthPoints = 50.0f;
	float StaminaPoints = 100.0f;
	float MaxStaminaPoints = 100.0f;
	float ManaPoints = 100.0f;
	float MaxManaPoints = 100.0f;
	float ManaRegen = 1.0f;
	float StaminaRegen = 10.0f;
	float HealthRegen = 0.0f;
	bool Mregen = true;
	bool Sregen = true;
	//Stats
};

