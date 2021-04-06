#include "Game.h"

Game::Game()
{

}

void Game::startGame()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenHeight, screenWidth), "SFML window");
    Player fucker({ 200.0f,180.0f });
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            dir.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            dir.x += 1;
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
}
