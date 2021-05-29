#include "Slime.h"

Slime::Slime(int id, int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor)
	:
	Enemy(type, pos, scaleFactor)
{
	this->pos = pos;
	//WAIFU SIZE 1,6m so 1,6m = 90px
	animations[int(AnimationIndex::Idle)] = SlimeAnimation(0, 0, "sprite/slime/idle/Idle (", "1", ").png", pTexture);
	animations[int(AnimationIndex::Moving)] = SlimeAnimation(0, 20, "sprite/slime/moving/Moving (", "1", ").png", pTexture);
    setTexture("sprite/slime/moving/Moving (1).png");
	enemyId = id;
	speedForce = 1;
	rotateForce = 0;
	jumpForce = 00;
    vel.x = 1.0f;
    speed = 50.0f;
    mass = 1.0f;
    Experience = 5.0f;
}

void Slime::rightCollision()
{
	speedForce = -speedForce;
	speedForce *= 0.9f;
	rotateForce = -rotateForce;
	rotateForce *= 0.9f;
    vel.x -= vel.x;
}

void Slime::leftCollision()
{
	speedForce = -speedForce;
	speedForce *= 0.9f;
	rotateForce = -rotateForce;
	rotateForce *= 0.9f;
    vel.x -= vel.x;
}

void Slime::SetDirection()
{
    //SETTING SPEED FOR JUMPING STATE
    if (validJump) {
        jumpSpeed = -jumpForce;
        //jumpForce *= 0.9;
    }
    else if (!validJump) {
       
    }
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
    /*speedForce *= 0.9998f;
    rotateForce *= 0.9998f;*/
    vel.x = speed * speedForce;
    vel.y = jumpSpeed;
    //SMART STUFF
    falling = true;
    validJump = false;
}

void Slime::Update(float dt)
{
    if (immunity)
    {
        immunityCooldown += dt;
        if (immunityCooldown >= 0.5f)
        {
            immunityCooldown = 0.0f;
            immunity = false;
            sprite.setColor(sf::Color(255, 255, 255));
        }
    }
    //SETTING CURRENT ANIMATION
    if (vel.y < 0) {
        //curAnimation = AnimationIndex::JumpUp;
        curAnimation = AnimationIndex::Moving;
    }
    else if (vel.y > 0) {
        //curAnimation = AnimationIndex::JumpDown;
        curAnimation = AnimationIndex::Moving;
    }
    else if (vel.x == 0.0f && vel.y == 0.0f) {
        curAnimation = AnimationIndex::Moving;
        //walking = false;
        //running = false;
    }
    else if (vel.x > 0) {
        //walking = true;
        //faceDir = 0;
        curAnimation = AnimationIndex::Moving;
    }
    else if (vel.x < 0) {
        //walking = true;
        //faceDir = 0;
        curAnimation = AnimationIndex::Moving;
    }
    if (vel.x > 0)
    {
        sprite.setScale({ -scaleFactor.x, scaleFactor.y });
    }
    else if (vel.x < 0)
    {
        sprite.setScale({ scaleFactor.x, scaleFactor.y });
    }

    pos += vel * dt;
    animations[int(curAnimation)].Update(dt);
    //SETTING FINAL POSITION TO SPRITE
    sprite.setPosition(pos);
    //ADDING ANIMATION TO SPRYTE
    animations[int(curAnimation)].ApplyToSprite(sprite);
}

Slime::SlimeAnimation::SlimeAnimation(int value_in, int frames_in, std::string str_1, std::string str_2, std::string str_3, std::shared_ptr<sf::Texture>& ptr)
{
    value = value_in;
    holdTime = 0.05f;
    str1 = str_1;
    str2 = str_2;
    str3 = str_3;
    nFrames = frames_in;
    std::string url = str1 + str2 + str3;

    int pos = 0;
    frame.reserve(nFrames);
    for (int i = 0; i < nFrames; i++) {
        str2 = std::to_string((pos++ + 1));
        url = str1 + str2 + str3;
        ptr = TextureCodex2::Acquire(url);
        frame.emplace_back(ptr);
    }
}

void Slime::SlimeAnimation::ApplyToSprite(sf::Sprite& s)
{
    if (!isTextureUpdated) {
        return;
    }
    isTextureUpdated = false;
    s.setTexture(*frame[iFrame]);
    s.setOrigin({ s.getLocalBounds().width / 2, s.getLocalBounds().height / 2 });
}

void Slime::SlimeAnimation::Update(float dt)
{
    time += dt;
    while (time >= holdTime) {
        time -= holdTime;
        Advance();
        isTextureUpdated = true;
    }
}

void Slime::SlimeAnimation::resetCounter()
{
    iFrame = 0;
}

bool Slime::SlimeAnimation::isLastFrame()
{
    if (iFrame == nFrames - 1) {
        return true;
    }
    return false;
}

void Slime::SlimeAnimation::Advance()
{
    if (++iFrame >= nFrames) { iFrame = 0; }
}
