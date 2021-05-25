#pragma once
#include "Enemy.h"
#include <vector>
class Slime : public Enemy
{
public:
	Slime(int id, int type, const sf::Vector2f& pos, const sf::Vector2f& scaleFactor);
	void rightCollision() override;
	void leftCollision() override;
    void SetDirection() override;
    void Update(float dt) override;
    //ANIMATION
private:
    class SlimeAnimation
    {
    public:
        SlimeAnimation() = default;
        SlimeAnimation(int value_in, int frames_in, std::string str_1, std::string str_2, std::string str_3, std::shared_ptr<sf::Texture>&);
        void ApplyToSprite(sf::Sprite& s);
        void Update(float dt);
        void resetCounter();
        bool isLastFrame();
    private:
        void Advance();
    private:
        bool isTextureUpdated = false;
        int nFrames = 0;
        float  holdTime = 0.0f;
        std::vector<std::shared_ptr<sf::Texture>> frame;
        int iFrame = 0;
        float time = 0.0f;
        std::string str1 = "";
        std::string str2 = "";
        std::string str3 = "";
        int value = 0;
    };
private:
    enum class AnimationIndex
    {
        Idle,
        Moving,
        Count
    };
    SlimeAnimation animations[int(AnimationIndex::Count)] = {};
    AnimationIndex curAnimation = AnimationIndex::Moving;
};

