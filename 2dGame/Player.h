#include "PlayerAnimation.h"
class Player {
public:
    Player(const sf::Vector2f& pos);
    void Draw(sf::RenderTarget& rt)const;
    void SetDirection(sf::Vector2f& dir);
    void Update(float dt);
    bool shift = false;
    bool jump = false;
private:
    enum class AnimationIndex
    {
        Idle,
        WalkingUp,
        WalkingDown,
        WalkingRight,
        WalkingLeft,
        RunUp,
        RunDown,
        RunRight,
        RunLeft,
        JumpUp,
        JumpDown,
        Count
    };
private:
    int jump_time = 90;
    bool faceDir = 0;
    bool walking = false;
    bool running = false;
    int time = 1;
    float speed = 70.0f;
    sf::Vector2f pos;
    sf::Vector2f vel = { 0.0f, 0.0f };
    sf::Sprite sprite;
    PlayerAnimation animations[int(AnimationIndex::Count)];
    AnimationIndex curAnimation = AnimationIndex::Idle;
};