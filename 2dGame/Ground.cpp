#include "Ground.h"

Ground::Ground(int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor)
    :
    pos(pos),
    type(type)
{
    if (type == int(GroundType::Ground)) 
    {
        texture.loadFromFile("sprite/grassBlock2.png");
        vel = { 0.0f, 0.0f };
        sprite.setTextureRect(sf::IntRect(0, 0, (int)(100 * scaleFactor.x), (int)(100 * scaleFactor.y)));
    }
    else if (type == int(GroundType::Water))
    {
        texture.loadFromFile("sprite/waterTexture1.png");
        vel = { -0.01f, -0.01f };
        sprite.setTextureRect(sf::IntRect(0, 0, (int)(100 * scaleFactor.x), (int)(100 * scaleFactor.y)));
    }
    else if (type == int(GroundType::Background))
    {
        texture.loadFromFile("sprite/firstLevelBackground.jpg");
        sprite.setTextureRect(sf::IntRect(0, 100, (int)(1360 * scaleFactor.x), (int)(720 * scaleFactor.y)));
    }

    texture.setRepeated(true);
    //texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(pos.x, pos.y);

    size = sprite.getLocalBounds();
}

void Ground::Draw(sf::RenderTarget& rt) const
{
    rt.draw(sprite);
}

void Ground::SetDirection()
{
    if (type == int(GroundType::Water)) {
        if (pos.y >= 760 - size.height/1.5)
        {
            vel.y = -0.005f;
        }
        else if (pos.y <= 680)
        {
            vel.y = 0.005f;
        }
        if (groundFlowTime >= 1.5f) {
            groundFlowTime = 0.0f;
            vel.x = -vel.x;
        }
    }
    pos += vel;
}

void Ground::Update(float dt)
{
    if (type == int(GroundType::Ground))
    {
        pos += vel * dt;
        sprite.setPosition(pos);
    }
    else if (type == int(GroundType::Water))
    {
        groundFlowTime += dt;
        sprite.setPosition(pos);
    }
}

sf::Vector2f Ground::GetPosition()
{
    return pos;
}

sf::FloatRect Ground::GetSize()
{
    return size;
}

int Ground::getType()
{
    return type;
}
