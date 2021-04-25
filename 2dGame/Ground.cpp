#include "Ground.h"

Ground::Ground(int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor)
    :
    pos(pos),
    type(type),
    scaleFactor(scaleFactor)
{
    if (type == int(GroundType::Ground)) 
    {
        pTexture = TextureCodex::Acquire("sprite/grassBlock2.png");
        vel = { 0.0f, 0.0f };
        sprite.setTextureRect(sf::IntRect(0, 0, (int)(100 * scaleFactor.x), (int)(100 * scaleFactor.y)));
    }
    else if (type == int(GroundType::Water))
    {
        pTexture = TextureCodex::Acquire("sprite/waterTexture1.png");
        vel = { -0.1f, -0.1f };
        sprite.setTextureRect(sf::IntRect(0, 0, (int)(100 * scaleFactor.x), (int)(100 * scaleFactor.y)));
    }
    else if (type == int(GroundType::Background))
    {
        pTexture = TextureCodex::Acquire("sprite/firstLevelBackground.jpg");
        sprite.setTextureRect(sf::IntRect(0, 100, (int)(1360 * scaleFactor.x), (int)(720 * scaleFactor.y)));
    }

    pTexture->setRepeated(true);
    sprite.setTexture(*pTexture);
    sprite.setPosition(pos.x, pos.y);

    size = sprite.getLocalBounds();
}

Ground::Ground(const Ground& source)
    :
    type(source.type),
    groundFlowTime(source.groundFlowTime),
    pTexture(source.pTexture),
    vel(source.vel),
    pos(source.pos),
    size(source.size),
    scaleFactor(source.scaleFactor)
{
    if (type == int(GroundType::Ground))
    {
        vel = { 0.0f, 0.0f };
        sprite.setTextureRect(sf::IntRect(0, 0, (int)(100 * scaleFactor.x), (int)(100 * scaleFactor.y)));
    }
    else if (type == int(GroundType::Water))
    {
        vel = { -0.1f, -0.1f };
        sprite.setTextureRect(sf::IntRect(0, 0, (int)(100 * scaleFactor.x), (int)(100 * scaleFactor.y)));
    }
    else if (type == int(GroundType::Background))
    {
        vel = { 0.0f, 0.0f };
        sprite.setTextureRect(sf::IntRect(0, 100, (int)(1360 * scaleFactor.x), (int)(720 * scaleFactor.y)));
    }

    sprite.setTexture(*pTexture);
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
            vel.y = -0.1f;
        }
        else if (pos.y <= 670)
        {
            vel.y = 0.1f;
        }
        if (groundFlowTime >= 5.0f) {
            groundFlowTime = 0.0f;
            vel.x = -vel.x;
        }
    }
    pos += vel;
}

void Ground::Update(float dt)
{
    if (type == int(GroundType::Water))
    {
        groundFlowTime += dt;
        sprite.setPosition(pos);
    }
    else
    {
        pos += vel * dt;
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

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> TextureCodex::textures;

std::shared_ptr<sf::Texture> TextureCodex::Acquire(const std::string& name)
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

void TextureCodex::Clean()
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