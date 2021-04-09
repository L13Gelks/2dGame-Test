#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class PlayerAnimation
{
    public:
        PlayerAnimation() = default;
        PlayerAnimation(int value_in, int frames_in, std::string str_1, std::string str_2, std::string str_3);
       /*~PlayerAnimation();
        PlayerAnimation(const PlayerAnimation& source);
        PlayerAnimation& operator=(const PlayerAnimation& source);*/
        void ApplyToSprite(sf::Sprite& s);
        void Update(float dt);
        void resetCounter();
        bool isLastFrame();
    private:
        void Advance();
    private:
        bool isTextureUpdated = false;
        sf::Texture texture;
        int nFrames = 0;
        float  holdTime = 0.0f;
        std::vector<sf::Texture> frame;
        int iFrame = 0;
        float time = 0.0f;
        std::string str1 = "";
        std::string str2 = "";
        std::string str3 = "";
        int value = 0;
};

