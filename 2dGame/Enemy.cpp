#include "Enemy.h"
Enemy::Enemy(int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor)
    :
    type(type),
    scaleFactor(scaleFactor)
{
    sprite.setScale(scaleFactor.x, scaleFactor.y);
    this->pos = pos;
}

Enemy::Enemy(const Enemy& source)
    :
    type(source.type),
    pTexture(source.pTexture),
    scaleFactor(source.scaleFactor),
    jumpForce(source.jumpForce),
    speedForce(source.speedForce),
    rotateForce(source.rotateForce),
    sprite(source.sprite)
{
    this->pos = source.pos;
    this->vel = source.vel;
    this->size = source.size;
    sprite.setTexture(*pTexture);
    //sprite.setScale(0.05f, 0.05f);
    size = sprite.getGlobalBounds();
    size.height = size.height / 2;
    sprite.setOrigin({ sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2 });
    speed = 100.0f;
}

void Enemy::Draw(sf::RenderTarget& rt) const
{
    rt.draw(sprite);
}

void Enemy::SetDirection()
{
    mass = 1;
    //SETTING SPEED FOR JUMPING STATE
    if (validJump) {
            jumpSpeed = -jumpForce;
            jumpForce *= 0.9f;
    }
    else if (!validJump) {
        if (!falling) {
            //STOP FALLING SPEED IF ON GROUND
            vel.y = 0.0f;
        }
        else
        {
            //INCREASE SPEED GRADUALLY UP T0 9,6m/s or 540px/s
            jumpSpeed += 540.0f / 60.0f;
            jumpSpeed *= mass;
            if (jumpSpeed >= 540.0f) {
                jumpSpeed = 540.0f;
            }
            
        }
    }
    speedForce *= 0.9998f;
    rotateForce *= 0.9998f;
    vel.x = speed * speedForce;
    vel.y = jumpSpeed;
    //SMART STUFF
    falling = true;
    validJump = false;
}

void Enemy::Update(float dt)
{
        pos += vel * dt;
        sprite.setPosition(pos);
        if (degrees >= 360) { degrees = 0; }
        degrees += rotateForce;
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

void Enemy::setPosition(sf::Vector2f& newPos)
{
    pos = newPos;
}

void Enemy::setTexture(std::string url)
{
    pTexture = TextureCodex2::Acquire(url);
    sprite.setTexture(*pTexture);
    sprite.setPosition(pos.x, pos.y);
    size = sprite.getGlobalBounds();
    size.height = size.height / 2;
    sprite.setOrigin({ sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2 });
}

void Enemy::rightCollision()
{
}

void Enemy::leftCollision()
{
}

void Enemy::setExperiencePoints(float exp)
{
    Experience = exp;
}

float Enemy::getExperiencePoints()
{
    return Experience;
}

void Enemy::setDamage(float dmg)
{
    if (!immunity)
    {
        HealthPoints -= dmg;
        sprite.setColor(sf::Color(255, 100, 100));
        immunity = true;
    }
}

void Enemy::setHealthPoints(float hp)
{
    HealthPoints = hp;
}

float Enemy::getHealthPoints()
{
    return HealthPoints;
}

void Enemy::setMaxHealthPoints(float mhp)
{
    MaxHealthPoints = mhp;
}

float Enemy::getMaxHealthPoints()
{
    return MaxHealthPoints;
}

void Enemy::setHealthPointsRegen(float hpr)
{
    HealthRegen = hpr;
}

float Enemy::getHealthPointsRegen()
{
    return HealthRegen;
}

void Enemy::setStaminaPoints(float sp)
{
    StaminaPoints = sp;
}

float Enemy::getStaminaPoints()
{
    return StaminaPoints;
}

void Enemy::setMaxStaminaPoints(float msp)
{
    MaxStaminaPoints = msp;
}

float Enemy::getMaxStaminaPoints()
{
    return MaxStaminaPoints;
}

void Enemy::setStaminaPointsRegen(float spr)
{
    StaminaRegen = spr;
}

float Enemy::getStaminaPointsRegen()
{
    return StaminaRegen;
}

void Enemy::setManaPoints(float mp)
{
    ManaPoints = mp;
}

float Enemy::getManaPoints()
{
    return ManaPoints;
}

void Enemy::setMaxManaPoints(float mmp)
{
    MaxManaPoints = mmp;
}

float Enemy::getMaxManaPoints()
{
    return MaxManaPoints;
}

void Enemy::setManaPointsRegen(float mpr)
{
    ManaRegen = mpr;
}

float Enemy::getManaPointsRegen()
{
    return Mregen;
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