#include "Game.h"

Game::Game()
{

}

Game::~Game()
{
}

void Game::WorldCreator()
{
    sf::Vector2f vec1 = { 0,0 };
    sf::Vector2f vec2 = { 0.0f,0.0f };
    float groundMult = 0.0f;
    ground.reserve(50);
    if (traveledDistance == 0.0f) {
        vec1 = { 0,0 };
        vec2 = { 9.0f,1.0f };
        ground.emplace_back(2, vec1, vec2);
        vec1 = { 0,670 };
        vec2 = { 140.0f,1.0f };
        ground.emplace_back(1, vec1, vec2);
        vec1 = { 0,610 };
        vec2 = { 14.0f,1.0f };
        groundMult = 14.0f;
        ground.emplace_back(0, vec1, vec2);
        travelGroundCheckPoint = groundMult * 100;
        bottomGroundIndex = 2;
        vec1 = { 500,550 };
        vec2 = { 1.0f,1.0f };
        enemy.emplace_back(1, vec1, vec2);
    }
    else {
        if (travelGroundCheckPoint == traveledDistance+screenWidth)
        {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> xDist(50, 200);
            std::uniform_int_distribution<int> xMult(1, 3);

            groundMult = xMult(rng);

            vec1 = { travelGroundCheckPoint,610 };
            vec2 = { groundMult,1.0f };

            ground.emplace_back(0, vec1, vec2);
            travelGroundCheckPoint += groundMult * 100;
            travelGroundCheckPoint += xDist(rng);
        }
    }
}

void Game::startGame()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Waifu Escape");
    auto image = sf::Image{};
    if (!image.loadFromFile("sprite/Run (7).png"))
    {
        // Error handling...
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    sf::View view(sf::FloatRect(0.f, 0.f, screenWidth, screenHeight));
    view.setCenter(sf::Vector2f(screenWidth / 2, screenHeight / 2));
    window.setView(view);
    Player fucker({ 200.0f,180.0f });
    //dt
    auto tp = std::chrono::steady_clock::now();
    // Start the game loop
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        WorldCreator();
        // get dt
        float dt;
        {
            const auto new_tp = std::chrono::steady_clock::now();
            dt = std::chrono::duration<float>(new_tp - tp).count();
            tp = new_tp;
        }
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        
   
        //handle input
        float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        sf::Vector2f dir = { 0.0f,1.0f };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || x < -10.f) {
            dir.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || x > 10.f) {
            dir.x += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Joystick::isButtonPressed(0, 5)) {
            fucker.SetShiftPressed(true);
        }
        else if (!fucker.IsJumping()) {
            fucker.SetShiftPressed(false);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1)) {
            fucker.SetJumping(true);
        }
        else 
        {
            fucker.SetJumping(false);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) || sf::Joystick::isButtonPressed(0, 4)) {
            dir.x = 0.0f;
            if (!fucker.IsJumping())
            {
                fucker.SetGuard(true);
            }
        }


        if (fucker.isHurting()) 
        {
            fucker.setHurtState(false);
        }


        fucker.SetDirection(dir);

        //update model
        fucker.Update(dt);
        // Clear screen
        window.clear();
        view.move(worldTravelSpeed, 0.0f);
        window.setView(view);
        // Draw the sprite
        ground[0].Draw(window);
        fucker.Draw(window);
        for (int e = 0; e < enemy.size(); e++)
        {
            enemy[e].SetDirection();
            int col = 0;
            sf::Vector2f enemyPos = { enemy[e].GetPosition().x - enemy[e].GetSize().width/2,enemy[e].GetPosition().y- enemy[e].GetSize().height/2 };
            if (e == 0) { col = TestCollision(fucker.GetSize(), fucker.GetPosition(), enemy[e].GetSize(),enemyPos); }
            if (col != 0)
            {
                sf::Vector2f newPos = fucker.GetPosition();
                newPos.y = enemyPos.y - fucker.GetSize().height + 1;
                fucker.validJump = true;
                fucker.falling = false;
                switch (col)
                {
                case 1:
                    break;
                case 2:
                    fucker.validJump = false;
                    fucker.falling = true;
                    newPos.x = enemyPos.x + enemy[e].GetSize().width + 2;
                    newPos.y = fucker.GetPosition().y;
                    break;
                case 3:
                    break;
                case 4:
                    fucker.validJump = false;
                    fucker.falling = true;
                    newPos.x = enemyPos.x - 2;
                    newPos.y = fucker.GetPosition().y;
                    break;
                default:
                    break;
                }
                fucker.setPosition(newPos);
            }
            enemy[e].Update(dt);

            enemy[e].Draw(window);

        }

        for (int g = 0; g < ground.size(); g++)
        {
            ground[g].SetDirection();
            int col = 0;
            if (g != 0) { col = TestCollision(fucker.GetSize(), fucker.GetPosition(), ground[g].GetSize(), ground[g].GetPosition()); }
            
            if (col != 0)
            {
                sf::Vector2f newPos = fucker.GetPosition();
                newPos.y = ground[g].GetPosition().y - fucker.GetSize().height + 1;
                fucker.validJump = true;
                fucker.falling = false;
                switch (col)
                {
                case 1:
                    break;
                case 2:
                    fucker.validJump = false;
                    fucker.falling = true;
                    newPos.x = ground[g].GetPosition().x + ground[g].GetSize().width + 2;
                    newPos.y = fucker.GetPosition().y;
                    break;
                case 3:
                    break;
                case 4:
                    fucker.validJump = false;
                    fucker.falling = true;
                    newPos.x = ground[g].GetPosition().x - 2;
                    newPos.y = fucker.GetPosition().y;
                    break;
                default:
                    break;
                }
                fucker.setPosition(newPos);
            }
            ground[g].Update(dt);
            if (g > 1)
            {
                ground[g].Draw(window);
            }
        }

        ground[1].Draw(window);
        // Update the window
        window.display();
        traveledDistance += worldTravelSpeed;
    }
}

int Game::TestCollision(const sf::FloatRect& obj_size1, const sf::Vector2f& obj_pos1, const sf::FloatRect& obj_size2, const sf::Vector2f& obj_pos2)
{

    if (obj_pos1.y + obj_size1.height >= obj_pos2.y && obj_pos1.y <= obj_pos2.y + obj_size2.height)
    {
        if (obj_pos1.x <= obj_pos2.x + obj_size2.width && obj_pos1.x >= obj_pos2.x) {
            if (obj_pos1.y + obj_size1.height-5 > obj_pos2.y && obj_pos1.y < obj_pos2.y + obj_size2.height)
            {
                if (obj_pos1.x + obj_size1.width >= obj_pos2.x && obj_pos1.x - 15 <= obj_pos2.x) {
                    //pos.x = pos_in.x - 2;
                    return 4;
                }
                else if (obj_pos1.x <= obj_pos2.x + obj_size2.width && obj_pos1.x + obj_size1.width >= obj_pos2.x + obj_size2.width)
                {
                    //pos.x = pos_in.x + size_in.width + 2;
                    return 2;
                }
            }
            return 1;
        }
    }
    return 0;
}

//Control buttons
//1 = X, 2 = O, 3 = triangle, 4 = square