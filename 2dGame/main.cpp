#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>  
#include <chrono>
#include "Player.h"




int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML window");
    Player fucker({ 200.0f,100.0f });
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