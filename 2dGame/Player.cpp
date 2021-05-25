#include "Player.h"

Player::Player(const sf::Vector2f& pos)
{
    this->pos = pos;
    //SIZE OF SPRITE 416x454 SCALED TO x0.2 = 83.2x90.8
    sprite.setScale(0.3f, 0.3f);
    //WAIFU SIZE 1,6m so 1,6m = 90px
    animations[int(AnimationIndex::Idle)] = PlayerAnimation(0, 16, "sprite/character/idle/Idle (", "1", ").png");
    animations[int(AnimationIndex::Walking)] = PlayerAnimation(1, 20, "sprite/character/jog/Jog (", "1", ").png");
    animations[int(AnimationIndex::Run)] = PlayerAnimation(2, 20, "sprite/character/run/Run (", "1", ").png");
    animations[int(AnimationIndex::JumpUp)] = PlayerAnimation(3, 12, "sprite/character/jump/Jump (", "1", ").png");
    animations[int(AnimationIndex::JumpDown)] = PlayerAnimation(4, 5, "sprite/character/jump/Jump (", "1", ").png");
    animations[int(AnimationIndex::Guard)] = PlayerAnimation(5, 16, "sprite/character/shield/Shield (", "1", ").png");
    animations[int(AnimationIndex::LightAttack)] = PlayerAnimation(6, 10, "sprite/character/attack/Attack (", "1", ").png");
    mass = 1.0f;
}

void Player::Draw(sf::RenderTarget& rt) const
{
    rt.draw(sprite);
}

void Player::SetDirection(sf::Vector2f& dir)
{
    //SETTING SPEED FOR WALKING OR RUNNING STATE
    if (shift || shiftPressed)
    {
        //180px/s = 3,2 m/s
        speed = 300.0f;
    }
    else {
        //90px/s = 1,6 m/s
        speed = 150.0f;
    }

    //SETTING SPEED FOR JUMPING STATE
    if (jump && validJump) {
        if (speed == 300.0f)
        {
            jumpSpeed = -80.0f * 4;
        }
        else if (speed == 150.0f) 
        {
            jumpSpeed = -80.0f * 3;
        }
    }
    //SETTING SPEED FOR FALLING STATE
    else if (!jump || !validJump)
    {
        if (!falling) {
            //STOP FALLING SPEED IF ON GROUND
            jumpSpeed = 0.0f;
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

    //ADDING SPEED MULTIPLIERS TO VELOCITY
    dir.x *= speed;
    dir.y *= jumpSpeed;
    vel = dir;

    //SMART STUFF
    falling = true;
    validJump = false;
}

void Player::Update(float dt)
{
    if (!atkAnimation) {
        //UPDATING POS
        pos += vel * dt;
        if (guard) {
            curAnimation = AnimationIndex::Guard;
            walking = false;
            running = false;
        }
        if (atk && jumpSpeed == 0) {
            curAnimation = AnimationIndex::LightAttack;
            walking = false;
            running = false;
            atkAnimation = true;
        }
        //SETTING CURRENT ANIMATION
        if (vel.y < 0) {
            curAnimation = AnimationIndex::JumpUp;
        }
        else if (vel.y > 0) {
            curAnimation = AnimationIndex::JumpDown;
        }
        else if (vel.x == 0.0f && vel.y == 0.0f && !guard && !atk) {
            curAnimation = AnimationIndex::Idle;
            walking = false;
            running = false;
        }
        else if (vel.x > 0) {
            if (!shiftPressed)
            {
                walking = true;
                faceDir = 0;
                curAnimation = AnimationIndex::Walking;
            }
            else
            {
                running = true;
                faceDir = 0;
                curAnimation = AnimationIndex::Run;
            }
        }
        else if (vel.x < 0) {
            if (!shiftPressed)
            {
                walking = true;
                faceDir = 1;
                curAnimation = AnimationIndex::Walking;
            }
            else
            {
                running = true;
                faceDir = 1;
                curAnimation = AnimationIndex::Run;
            }
        }
        if (vel.x < 0)
        {
            sprite.setScale({ -0.3f, 0.3f });
        }
        else if (vel.x > 0)
        {
            sprite.setScale({ 0.3f, 0.3f });
        }
        //CHECKING IF BY THE TIME OF JUMP SHIFT WAS PRESSED
        if (lastAnimation != curAnimation) {
            if (curAnimation == AnimationIndex::JumpUp && lastAnimation == AnimationIndex::Run)
            {
                shiftPressed = true;
            }
            animations[int(lastAnimation)].resetCounter();
            lastAnimation = curAnimation;
        }

        //CHECKING IF JUMP UP OR JUMP DOWN ANIMATION MUST BE USED
        if (curAnimation == AnimationIndex::JumpUp && animations[int(curAnimation)].isLastFrame() ||
            curAnimation == AnimationIndex::JumpDown && animations[int(curAnimation)].isLastFrame())
        {
        }
        else
        {
            animations[int(curAnimation)].Update(dt);
            //SETTING SHIFT STATE TO FALSE WHEN JUMP ANIAMTION ENDS
            if (curAnimation != AnimationIndex::JumpUp && curAnimation != AnimationIndex::JumpDown) { shiftPressed = false; }
        }
        //SETTING FINAL POSITION TO SPRITE
        sprite.setPosition(pos);
    }
    else {
        animations[int(curAnimation)].Update(dt);
        if(animations[int(curAnimation)].isLastFrame())
        {
            atkAnimation = false;
            atk = false;
        }
    }
    //ADDING ANIMATION TO SPRYTE
    if (guard) {
        guard = false;
    }
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

/*
bool Player::TestCollision(const  sf::FloatRect& size_in, const sf::Vector2f& pos_in, int type)
{
    sf::FloatRect vec = sprite.getGlobalBounds();

    //IF BACKGROUND GET OUT OF HERE BUDDY
    if (type == 2)
    {
        return 0;
    }

    //ASSUMING PLAYER MUST BE ON TOP OF GROUND...
    float newPos = pos_in.y - vec.height + 1;

    if (pos.y + vec.height >= pos_in.y && pos.y <= pos_in.y + size_in.height)
    {
        if (pos.x <= pos_in.x + size_in.width && pos.x >= pos_in.x) {
            //IF ON GROUND NOW YOU CAN JUMP AND STOP GOING DOWN 
            validJump = true;
            falling = false;

            //ASSUMING PLAYER MUST NOT AUTO-JUMP ON TILES IF CERTAIN HEIGHT...
            if (pos.y + vec.height > pos_in.y + size_in.height / 8)
            {
                if (pos.x + vec.width / 2 >= pos_in.x && pos.x - vec.width / 2 <= pos_in.x ) {
                    pos.x = pos_in.x - 2;
                }
                else if (pos.x <= pos_in.x + size_in.width && pos.x + vec.width/2 >= pos_in.x + size_in.width)
                {
                    pos.x = pos_in.x + size_in.width + 2;
                }

                //ASSUMING PLAYER MUST NOT BE ON TOP OF GROUND...
                newPos = pos.y;

                //SETTING THESE VALUES IF LATERAL COLISSION OCCURS
                validJump = false;
                falling = true;
            }

            //SETTING THE CORRECT POSTION BASED ON WHATEVER
            pos.y = newPos;

            //IF DANGEROUS GROUND GG
            if (type == 1) { hurt = true; }
        }
    }
    //SETTING POS IF COLISSION WAS DETECTED
    sprite.setPosition(pos);
    //IF IT HURTS CHANGED COLOR TO SOMETHING REDDISH IF NOT THEN WHATEVER
    if (hurt == true) { sprite.setColor(sf::Color(255, 100, 100)); }
    else { sprite.setColor(sf::Color(255, 255, 255)); }

    //WHY
    return false;
}
*/

void Player::setHurtState(bool state)
{
    hurt = state;
}

void Player::SetGuard(bool state)
{
    guard = state;
}

bool Player::isHurting()
{
    return hurt;
}

sf::Vector2f Player::GetPosition()
{
    return pos;
}

sf::FloatRect Player::GetSize()
{
    size = sprite.getGlobalBounds();
    size.height = size.height * 0.75f;
    return size;
}

int Player::getType()
{
    return 100;
}

void Player::setPosition(sf::Vector2f& newPos)
{
    pos = newPos;
}

