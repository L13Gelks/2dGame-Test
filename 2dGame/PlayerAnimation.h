#pragma once
#include <SFML/Graphics.hpp>
class PlayerAnimation
{
    public:
        PlayerAnimation() = default;
        PlayerAnimation(int value_in, int frames_in, std::string str_1, std::string str_2, std::string str_3)
        {
            value = value_in;
            str1 = str_1;
            str2 = str_2;
            str3 = str_3;
            nFrames = frames_in;
            std::string url = str1 + str2 + str3;
            texture.loadFromFile(url);
            for (int i = 0; i < nFrames; i++) {
                str2 = std::to_string((i + 1));
                url = str1 + str2 + str3;
                frames[i] = { url };
            }
        }

        void ApplyToSprite(sf::Sprite& s) {

            texture.loadFromFile(frames[iFrame]);
            s.setTexture(texture);
            s.setOrigin({ s.getLocalBounds().width / 2, 0 });

            if (value == 2) {
                //left

                s.setScale({ -0.2, 0.2 });
            }
            else if (value == 1) {
                //right
                s.setScale({ 0.2, 0.2 });

            }
            else {

            }
        }
        void Update(float dt) {
            time += dt;
            while (time >= holdTime) {
                time -= holdTime;
                Advance();
            }
        }
    private:
        void Advance() {
            if (++iFrame >= nFrames) { iFrame = 0; }
        }
    private:
        sf::Texture texture;
        int nFrames = 0;
        static constexpr float  holdTime = 0.06f;
        std::string frames[30];
        int iFrame = 0;
        float time = 0.0f;
        std::string str1 = "";
        std::string str2 = "";
        std::string str3 = "";
        int value = 0;
        bool changed = false;
};

