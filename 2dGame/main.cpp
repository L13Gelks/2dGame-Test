#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>  
#include <chrono>

class Animation {
public:
    Animation() = default;
    Animation(int value_in, int frames_in, std::string str_1, std::string str_2, std::string str_3)
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

class Character {
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
        Jump,
        Count
    };
public:
    bool shift = false;
    bool jump = false;
    Character(const sf::Vector2f& pos)
        :
        pos(pos)
    {
        sprite.setScale(0.2, 0.2);
        animations[int(AnimationIndex::Idle)] = Animation(0, 16, "sprite/Idle (", "1", ").png");
        animations[int(AnimationIndex::WalkingRight)] = Animation(1, 20, "sprite/Walk (", "1", ").png");
        animations[int(AnimationIndex::WalkingLeft)] = Animation(2, 20, "sprite/Walk (", "1", ").png");
        animations[int(AnimationIndex::RunRight)] = Animation(1, 20, "sprite/Run (", "1", ").png");
        animations[int(AnimationIndex::RunLeft)] = Animation(2, 20, "sprite/Run (", "1", ").png");
        animations[int(AnimationIndex::Jump)] = Animation(0, 30, "sprite/Jump (", "1", ").png");
    }
    void Draw(sf::RenderTarget& rt)const
    {
        rt.draw(sprite);
    }
    void SetDirection(sf::Vector2f& dir) {
        if (jump) {
            time += 1;

            if (time < jump_time / 2) { dir.y -= 1; }
            else { dir.y += 1; }

            if (!walking && !running) {
                if (faceDir) { dir.x = -0.2; }
                else { dir.x = 0.2; }
                dir.y *= 0.5;
            }
            else if (walking) {
                if (faceDir) { dir.x = -0.4; }
                else { dir.x = 0.4; }
                dir.y *= 0.6;
            }
            else if (running) {
                if (faceDir) { dir.x = -1.4; }
                else { dir.x = 1.4; }
                dir.y *= 0.8;
            }


            if (time > jump_time) {
                jump = false;
                time = 0;
                vel.y = 0;
                jump_time = 90;
            }
        }
        if (shift)
        {
            speed = 150.0f;
        }
        else {
            speed = 70.0f;
        }
        vel = dir * speed;
        if (!jump && sprite.getPosition().y < 400) {
            dir.y = 2;
            dir.x = 0;
            vel = dir * speed;
        }
        else if (dir.y != 0) {
            curAnimation = AnimationIndex::Jump;
        }
        else if (dir.x == 0.0f && dir.y == 0.0f) {
            curAnimation = AnimationIndex::Idle;
            walking = false;
            running = false;
        }
        else if (dir.x > 0 && shift) {
            running = true;
            faceDir = 0;
            curAnimation = AnimationIndex::RunRight;
        }
        else if (dir.x < 0 && shift) {
            running = true;
            faceDir = 1;
            curAnimation = AnimationIndex::RunLeft;
        }
        else if (dir.x > 0) {
            walking = true;
            faceDir = 0;
            curAnimation = AnimationIndex::WalkingRight;
        }
        else if (dir.x < 0) {
            walking = true;
            faceDir = 1;
            curAnimation = AnimationIndex::WalkingLeft;
        }
        if (sprite.getPosition().y > 400) {
            pos.y = 400;
            sprite.setPosition(pos);
            vel.y = 0;
        }
    }
    void Update(float dt) {

        pos += vel * dt;
        animations[int(curAnimation)].Update(dt);
        animations[int(curAnimation)].ApplyToSprite(sprite);

        sprite.setPosition(pos);
    }
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
    Animation animations[int(AnimationIndex::Count)];
    AnimationIndex curAnimation = AnimationIndex::Idle;

};
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML window");
    Character fucker({ 200.0f,100.0f });
    //dt
    auto tp = std::chrono::steady_clock::now();
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // get dt
        float dt;
        {
            const auto new_tp = std::chrono::steady_clock::now();
            dt = std::chrono::duration<float>(new_tp - tp).count();
            tp = new_tp;
        }
        //handle input
        sf::Vector2f dir = { 0.0f,0.0f };
        if (!fucker.jump && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            /*dir.y -= 1;*/
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            /*dir.y += 1;*/
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            dir.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            dir.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
            fucker.shift = true;
        }
        else {
            fucker.shift = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            fucker.jump = true;
        }

        /*dir.y += 1;*/
        fucker.SetDirection(dir);
        //update model
        fucker.Update(dt);
        // Clear screen
        window.clear();
        // Draw the sprite
        fucker.Draw(window);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}