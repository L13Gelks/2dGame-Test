#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation(int value_in, int frames_in, std::string str_1, std::string str_2, std::string str_3)
{
    value = value_in;
    if (value != 3 && value != 4) {
        //Normal animation time
        holdTime = 0.05f;
    }
    else  { holdTime = 0.08f; } //Jump animation time

    str1 = str_1;
    str2 = str_2;
    str3 = str_3;
    nFrames = frames_in;
    std::string url = str1 + str2 + str3;

    int pos = 0;
    if (value_in != 4) { pos = 0; }
    else { pos = 15; }

    frame.reserve(nFrames);

    for (int i = 0; i < nFrames; i++) {
        
        str2 = std::to_string((pos++ + 1));
        url = str1 + str2 + str3;
        texture.loadFromFile(url);
        frame.emplace_back(texture);
    }
}

/*PlayerAnimation::~PlayerAnimation()
{
}

PlayerAnimation& PlayerAnimation::operator=(const PlayerAnimation& source)
{
    delete[] frame;
    frame = nullptr;

    frame = new sf::Texture[source.nFrames];
    nFrames = source.nFrames;

    for (int i = 0; i < nFrames; i++) {
        frame[i] = source.frame[i];
    }
    return *this;
}*/

void PlayerAnimation::ApplyToSprite(sf::Sprite& s)
{
    if (!isTextureUpdated) { 
        return; 
    }
    isTextureUpdated = false;
    s.setTexture(frame[iFrame]);
    s.setOrigin({ s.getLocalBounds().width / 2, 0 });
}

void PlayerAnimation::Update(float dt)
{
    time += dt;
    while (time >= holdTime) {
        time -= holdTime;
        Advance();
        isTextureUpdated = true;
    }
}

void PlayerAnimation::resetCounter()
{
    iFrame = 0;
}

bool PlayerAnimation::isLastFrame()
{
    if (iFrame == nFrames - 1) {
        return true;
    }
    return false;
}

void PlayerAnimation::Advance()
{
    if (++iFrame >= nFrames) { iFrame = 0; }
}
