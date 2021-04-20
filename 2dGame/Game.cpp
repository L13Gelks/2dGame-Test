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
        sf::Vector2f dir = { 0.0f,1.0f };
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            dir.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            dir.x += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
            fucker.SetShiftPressed(true);
        }
        else if (!fucker.IsJumping()) {
            fucker.SetShiftPressed(false);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            fucker.SetJumping(true);
        }
        else 
        {
            fucker.SetJumping(false);
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
        for (int i = 0; i < ground.size(); i++)
        {
            ground[i].SetDirection();
            fucker.TestCollision(ground[i].GetSize(), ground[i].GetPosition(), ground[i].getType());
            ground[i].Update(dt);
            if (i > 1)
            {
                ground[i].Draw(window);
            }
        }
        ground[1].Draw(window);
        // Update the window
        window.display();
        traveledDistance += worldTravelSpeed;
    }
}
