#include "Player.h"

Player::Player(const sf::Vector2f& pos)
    :
    pos(pos)
{
    sprite.setScale(0.2, 0.2);
    animations[int(AnimationIndex::Idle)] = PlayerAnimation(0, 16, "sprite/Idle (", "1", ").png");
    animations[int(AnimationIndex::WalkingRight)] = PlayerAnimation(1, 20, "sprite/Walk (", "1", ").png");
    animations[int(AnimationIndex::WalkingLeft)] = PlayerAnimation(2, 20, "sprite/Walk (", "1", ").png");
    animations[int(AnimationIndex::RunRight)] = PlayerAnimation(1, 20, "sprite/Run (", "1", ").png");
    animations[int(AnimationIndex::RunLeft)] = PlayerAnimation(2, 20, "sprite/Run (", "1", ").png");
    animations[int(AnimationIndex::JumpUp)] = PlayerAnimation(3, 20, "sprite/Jump (", "1", ").png");
    animations[int(AnimationIndex::JumpDown)] = PlayerAnimation(4, 6, "sprite/Jump (", "21", ").png");
    //sprite.setTextureRect(sf::IntRect(0,0,416,454));
}

void Player::Draw(sf::RenderTarget& rt) const
{
    rt.draw(sprite);
}

void Player::SetDirection(sf::Vector2f& dir)
{
    if (jump) {

        time += 1;
        if (time < jump_time / 2) { dir.y -= 1; }
        else { dir.y += 1; }

        if (!walking && !running && !shiftPressed) {
            if (faceDir) { dir.x = -0.2f; }
            else { dir.x = 0.2f; }
            dir.y *= 0.5f;
        }
        else if (walking && !shiftPressed) {
            if (faceDir) { dir.x = -0.4f; }
            else { dir.x = 0.4f; }
            dir.y *= 0.6f;
        }
        else if (running || shiftPressed) {
            if (faceDir) { dir.x = -1.4f; }
            else { dir.x = 1.4f; }
            dir.y *= 0.8f;
        }

        if (time > jump_time) {
            jump = false;
            time = 0;
            vel.y = 0;
        }
    }

    if (shift || shiftPressed)
    {
        speed = 150.0f;
    }
    else {
        speed = 70.0f;
    }

    //Set Movement
 
    if (!jump && !lockY) {
        dir.y += 2;
    }
    if (dir.y < 0) {
        curAnimation = AnimationIndex::JumpUp;
    }
    else if (dir.y > 0) {
        curAnimation = AnimationIndex::JumpDown;
    }
    else if (!jump && dir.x == 0.0f && dir.y == 0.0f) {
        curAnimation = AnimationIndex::Idle;
        walking = false;
        running = false;
    }
    else if (!jump && dir.x > 0 && shift) {
        running = true;
        faceDir = 0;
        curAnimation = AnimationIndex::RunRight;
    }
    else if (!jump && dir.x < 0 && shift) {
        running = true;
        faceDir = 1;
        curAnimation = AnimationIndex::RunLeft;
    }
    else if (!jump && dir.x > 0) {
        walking = true;
        faceDir = 0;
        curAnimation = AnimationIndex::WalkingRight;
    }
    else if (!jump && dir.x < 0) {
        walking = true;
        faceDir = 1;
        curAnimation = AnimationIndex::WalkingLeft;
    }
    vel = dir * speed;
}

void Player::Update(float dt)
{
    if (lockX) { vel.x = 0; }
    if (lockY) { vel.y = 0; }
    lockX = false; lockY = false;

    pos += vel * dt;
    if (lastAnimation != curAnimation) {
        if (curAnimation == AnimationIndex::JumpUp && lastAnimation ==AnimationIndex::RunRight ||
            curAnimation == AnimationIndex::JumpUp && lastAnimation == AnimationIndex::RunLeft) 
        { 
            shiftPressed = true; 
        }
        animations[int(lastAnimation)].resetCounter();
        lastAnimation = curAnimation;
    }

    if (curAnimation == AnimationIndex::JumpUp && animations[int(curAnimation)].isLastFrame() ||
        curAnimation == AnimationIndex::JumpDown && animations[int(curAnimation)].isLastFrame()) 
    {}
    else 
    { 
        animations[int(curAnimation)].Update(dt); 
        if (curAnimation != AnimationIndex::JumpUp && curAnimation != AnimationIndex::JumpDown) { shiftPressed = false; }
    }

    sprite.setPosition(pos);
    animations[int(curAnimation)].ApplyToSprite(sprite);

}

bool Player::IsJumping() const
{
    return jump;
}

bool Player::IsShiftPressed() const
{
    return shiftPressed;
}

void Player::SetJumping(bool jumping)
{
    jump = jumping;
}

void Player::SetShiftPressed(bool shiftp)
{
    shiftPressed = shiftp;
}

bool Player::TestCollision(const  sf::FloatRect& size_in, const sf::Vector2f& pos_in)
{

    sf::FloatRect vec = sprite.getGlobalBounds();
    vec;

    if (pos.y + vec.height >= pos_in.y && pos.x <= pos_in.x + size_in.width && pos.x + vec.width >= pos_in.x)
    {
        if (!jump)
        {
            lockY = true;
        }
 
        if (pos.y + vec.height > pos_in.y)
        {
            pos.y = pos_in.y - vec.height;
            sprite.setPosition(pos);
        }
    }
    else 
    {
        if (pos.y + vec.height > pos_in.y && pos.x >= pos_in.x + size_in.width ||
            pos.y + vec.height > pos_in.y && pos.x + vec.width <= pos_in.x)
        {
            lockX = true;
        }
    }

    return false;
}


