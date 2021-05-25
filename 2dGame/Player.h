#include "PlayerAnimation.h"
#include "Entity.h"

class Player : public Entity{
public:
    Player(const sf::Vector2f& pos);
    void Draw(sf::RenderTarget& rt)const;
    void SetDirection(sf::Vector2f& dir);
    void Update(float dt);
    bool IsJumping() const;
    bool IsShiftPressed() const;
    void SetJumping(bool jumping);
    void SetShiftPressed(bool shiftp);
    void setHurtState(bool state);
    void SetGuard(bool state);
    bool isHurting();
    sf::Vector2f GetPosition();
    sf::FloatRect GetSize();
    int getType();
    void setPosition(sf::Vector2f& newPos);
    bool atk = false;
    bool atkAnimation = false;
private:

private:
    enum class AnimationIndex
    {
        Idle,
        Walking,
        Run,
        JumpUp,
        JumpDown,
        Guard,
        LightAttack,
        Count
    };
private:
    bool jump = false;
    bool guard = false;
    float jumpSpeed = 0.0f;
    bool hurt = false;
    bool faceDir = 0;
    bool walking = false;
    bool running = false;
    bool shiftPressed = false;
    bool shift = false;
    sf::Sprite sprite;
    sf::FloatRect size;
    PlayerAnimation animations[int(AnimationIndex::Count)] = {};
    AnimationIndex curAnimation = AnimationIndex::Idle;
    AnimationIndex lastAnimation = AnimationIndex::Idle;
};