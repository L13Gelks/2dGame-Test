#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <string>

class TextureCodex
{
public:
	static std::shared_ptr<sf::Texture> Acquire(const std::string& name);
	static void Clean();
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
};


class Ground
{
public:
	Ground(int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor);
	Ground(const Ground& source);
	Ground& operator=(const Ground&) = delete;
	void Draw(sf::RenderTarget& rt)const;
	void SetDirection();
	void Update(float dt);
	sf::Vector2f GetPosition();
	sf::FloatRect GetSize();
	int getType();
	void setTileStart(float in);
	float getTileStart();
	void setTileEnd(float in);
	float getTileEnd();
	void setTileLength(float in);
	float getTileLength();
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
	std::shared_ptr<sf::Texture> pTexture;
	sf::Sprite sprite;
	sf::Vector2f vel = { 0.0f, 0.0f };
	sf::Vector2f pos;
	sf::Vector2f scaleFactor;
	sf::FloatRect size;
	float tileStart = 0.0f;
	float tileEnd = 0.0f;
	float tileLength = 0.0f;
};

