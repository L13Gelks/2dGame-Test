#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation(int value_in, int frames_in, std::string str_1, std::string str_2, std::string str_3)
{
    value = value_in;
    str1 = str_1;
    str2 = str_2;
    str3 = str_3;
    nFrames = frames_in;
    std::string url = str1 + str2 + str3;
    texture.loadFromFile(url);
    int pos = 0;
    if (value_in != 4) { pos = 0; }
    else { pos = 15; }

    for (int i = 0; i < nFrames; i++) {
        
        str2 = std::to_string((pos++ + 1));
        url = str1 + str2 + str3;
        frames[i] = { url };
    }
}

void PlayerAnimation::ApplyToSprite(sf::Sprite& s)
{
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

void PlayerAnimation::Update(float dt)
{
    time += dt;
    while (time >= holdTime) {
        time -= holdTime;
        Advance();
    }
}

void PlayerAnimation::Advance()
{
    if (++iFrame >= nFrames) { iFrame = 0; }
}
