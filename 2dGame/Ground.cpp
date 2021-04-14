#include "Ground.h"

Ground::Ground(const sf::Vector2f& pos, const sf::Vector2f& scaleFactor)
    :
    pos(pos)
{
    texture.loadFromFile("sprite/grassBlock.jpg");
    sprite.setTexture(texture);
    sprite.setPosition(pos.x, pos.y);
    sprite.setTextureRect(sf::IntRect(0, 0, sprite.getLocalBounds().width * scaleFactor.x, sprite.getLocalBounds().height * scaleFactor.y));
    size = sprite.getLocalBounds();
}

void Ground::Draw(sf::RenderTarget& rt) const
{
    rt.draw(sprite);
}

void Ground::SetDirection()
{
    pos += vel;
}

void Ground::Update(float dt)
{
    //pos += vel * dt;
    //sprite.setPosition(pos);
}

sf::Vector2f Ground::GetPosition()
{
    return pos;
}

sf::FloatRect Ground::GetSize()
{
    return size;
}
