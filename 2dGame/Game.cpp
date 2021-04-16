#include "Game.h"

Game::Game()
{

}

Game::~Game()
{
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
    Player fucker({ 200.0f,180.0f });
    sf::Vector2f vec1 = { 0,610 };
    sf::Vector2f vec2 = { 2.0f,1.0f };

    Ground ground(0,vec1,vec2);
    vec1 = { 700,590 };
    vec2 = { 4.0f,1.0f };
    Ground ground2(0,vec1, vec2);
    vec1 = { 0,670 };
    vec2 = { 14.0f,1.0f };
    Ground water(1, vec1, vec2);
    vec1 = { 0,0 };
    vec2 = { 1.0f,1.0f };
    Ground background(2, vec1, vec2);
    //dt
    auto tp = std::chrono::steady_clock::now();
    // Start the game loop
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
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
        water.SetDirection();
        ground.SetDirection();

       
        fucker.TestCollision(ground2.GetSize(), ground2.GetPosition(), 0);
        fucker.TestCollision(water.GetSize(), water.GetPosition(), 1);
        fucker.TestCollision(ground.GetSize(), ground.GetPosition(), 0);
        //update model
        fucker.Update(dt);
        ground.Update(dt);
        water.Update(dt);
        // Clear screen
        window.clear();
        // Draw the sprite
        background.Draw(window);
        fucker.Draw(window);
        ground.Draw(window);
        ground2.Draw(window);
        water.Draw(window);
        // Update the window
        window.display();
    }
}
