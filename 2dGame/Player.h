#include "PlayerAnimation.h"
class Player {
public:
    Player(const sf::Vector2f& pos);
    void Draw(sf::RenderTarget& rt)const;
    void SetDirection(sf::Vector2f& dir);
    void Update(float dt);
    bool IsJumping() const;
    bool IsShiftPressed() const;
    void SetJumping(bool jumping);
    void SetShiftPressed(bool shiftp);
    bool TestCollision(const sf::FloatRect& size, const sf::Vector2f& pos, int type);
    void setHurtState(bool state);
    void SetGuard(bool state);
    bool isHurting();
    sf::Vector2f GetPosition();
    sf::FloatRect GetSize();
    int getType();
    void setPosition(sf::Vector2f& newPos);
    bool validJump = false;
    bool falling = true;
private:
    enum class AnimationIndex
    {
        Idle,
        Walking,
        Run,
        JumpUp,
        JumpDown,
        Guard,
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
    float speed = 0.0f;
    sf::Vector2f pos;
    sf::FloatRect size;
    sf::Vector2f vel = { 0.0f, 0.0f };
    sf::Sprite sprite;
    PlayerAnimation animations[int(AnimationIndex::Count)] = {};
    AnimationIndex curAnimation = AnimationIndex::Idle;
    AnimationIndex lastAnimation = AnimationIndex::Idle;
};