#include "Enemy.h"
Enemy::Enemy(int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor)
    :
    pos(pos),
    type(type),
    scaleFactor(scaleFactor)
{

        pTexture = TextureCodex2::Acquire("sprite/ball.png");
        vel = { 1.0f, 0.0f };
    

    sprite.setTexture(*pTexture);
    sprite.setPosition(pos.x, pos.y);
    sprite.setScale(0.05f,0.05f);
    size = sprite.getGlobalBounds();
    sprite.setOrigin({ sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2 });
    
}

Enemy::Enemy(const Enemy& source)
    :
    type(source.type),
    pTexture(source.pTexture),
    vel(source.vel),
    pos(source.pos),
    size(source.size),
    scaleFactor(source.scaleFactor)
{

        vel = { 0.0f, 0.0f };
       


    sprite.setTexture(*pTexture);
}

void Enemy::Draw(sf::RenderTarget& rt) const
{
    rt.draw(sprite);
}

void Enemy::SetDirection()
{
    pos += vel;
}

void Enemy::Update(float dt)
{

        pos += vel * dt;
        sprite.setPosition(pos);
        if (degrees >= 360) { degrees = 0; }
        degrees += 1;
        sprite.setRotation(degrees);
}

sf::Vector2f Enemy::GetPosition()
{
    return pos;
}

sf::FloatRect Enemy::GetSize()
{
    return size;
}

int Enemy::getType()
{
    return type;
}

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> TextureCodex2::textures;

std::shared_ptr<sf::Texture> TextureCodex2::Acquire(const std::string& name)
{
    const auto i = textures.find(name);
    if (i != textures.end())
    {
        return i->second;
    }
    else
    {
        auto pTexture = std::make_shared<sf::Texture>();
        pTexture->loadFromFile(name);
        textures.insert({ name,pTexture });
        return pTexture;
    }
}

void TextureCodex2::Clean()
{
    for (auto i = textures.begin(); i != textures.end();)
    {
        if (i->second.unique())
        {
            i = textures.erase(i);
        }
        else
        {
            ++i;
        }
    }
}