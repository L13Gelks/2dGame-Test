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
        traveledDistance += 0.1f;
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
        //
        ground.at(ground.size()-1).setTileStart(travelGroundCheckPoint);
        ground.at(ground.size()-1).setTileEnd(groundMult * 100);
        ground.at(ground.size()-1).setTileLength(groundMult * 100);
        //
        travelGroundCheckPoint = groundMult * 100;
        bottomGroundIndex = 2;
        vec1 = { 500,550 };
        vec2 = { 0.05f, 0.05f };
        PelotaMiedo* e = new PelotaMiedo(0,1, vec1, vec2);
       // enemy.push_back(e);
        vec1 = { 500,350 };
        vec2 = { 0.3f,0.3f };
        Slime* a = new Slime(1, 1, vec1, vec2);
        enemy.push_back(a);
    }
    else {
        if (travelGroundCheckPoint >= traveledDistance+screenWidth-10 && travelGroundCheckPoint <= traveledDistance + screenWidth + 10)
        {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> xDist(50, 200);
            std::uniform_int_distribution<int> xMult(1, 3);
            //std::uniform_int_distribution<int> xMult(10, 300);

            groundMult = xMult(rng);

            vec1 = { travelGroundCheckPoint,610 };
            vec2 = { groundMult,1.0f };

            ground.emplace_back(0, vec1, vec2);
            travelGroundCheckPoint += (float)groundMult * 100.0f;
            travelGroundCheckPoint += xDist(rng);
        }
    }
}

void Game::startGame()
{
    Menu menu(screenWidth, screenHeight);
    Hud hud(screenWidth, screenHeight);
    sf::Font font;
    if (!font.loadFromFile("Font/arial.ttf"))
    {
        // error...
    }
    text.setFont(font);
    text.setString("Hello world");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Waifu's Souls");
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
        playerPosX = fucker.GetPosition().x;
        WorldCreator();
        // get dt
        dt = 0.0f;
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
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Escape) {
                    menuPressed = !menuPressed;
                }
                else if (menuPressed && event.key.code == sf::Keyboard::Left)
                {
                    menu.MoveUp();
                }
                else if (menuPressed && event.key.code == sf::Keyboard::Right)
                {
                    menu.MoveDown();
                }
                break;
            default:
                break;
            }
        }

        if (!menuPressed)
        {
            //handle input
            PlayerInput(fucker);
        }
        else {

        }
        //update model
        fucker.Update(dt);
        // Clear screen
        window.clear();
        // Draw the sprite
        if (!menuPressed) {
            ground[0].Draw(window);
            fucker.Draw(window);
        }

        enemyPhysics(fucker,window);

        //Player with world
        for (int g = 0; g < ground.size(); g++)
        {
            ground[g].SetDirection();
            int col = 0;
            if (g != 0) { col = TestCollision(fucker.GetSize(), fucker.GetPosition(), ground[g].GetSize(), ground[g].GetPosition()); }
            
            if (col != 0)
            {
                if(ground[g].getType() == 1)
                {
                    fucker.setHurtState(true);
                    fucker.setDamage(0.5f);
                }
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
            if (g > 1 && !menuPressed)
            {
                ground[g].Draw(window);
            }
        }

        playerLastPosX = fucker.GetPosition().x;
        playerMoveX = playerLastPosX - playerPosX;

        if (fucker.GetPosition().x >= 680)
        {
            view.move(playerMoveX, 0.0f);
            window.setView(view);
        }
        if (!menuPressed) {
            sf::Vector2f pos = { view.getCenter().x - screenWidth / 2, view.getCenter().y - screenHeight / 2 };
            ground[1].Draw(window);
            hud.setPosition(pos);
            hud.setStats(fucker);
            hud.draw(window);
        }
        if (menuPressed) {
            sf::Vector2f pos = { view.getCenter().x - screenWidth / 2, view.getCenter().y - screenHeight / 2 };
            menu.setPosition(pos);
            menu.draw(window);
            switch (menu.getOption())
            {
            case 1:
                menu.showStats(window,fucker);
                break;
            default:
                break;
            }
        }
        // Update the window
        checkButton(window);
        window.display();
        
        traveledDistance += playerMoveX;

    }
}

int Game::TestCollision(const sf::FloatRect& obj_size1, const sf::Vector2f& obj_pos1, const sf::FloatRect& obj_size2, const sf::Vector2f& obj_pos2)
{

    if (obj_pos1.y + obj_size1.height >= obj_pos2.y && obj_pos1.y <= obj_pos2.y + obj_size2.height)
    {
        if (obj_pos1.x <= obj_pos2.x + obj_size2.width && obj_pos1.x >= obj_pos2.x) {
            if (obj_pos1.y + obj_size1.height-10 > obj_pos2.y && obj_pos1.y < obj_pos2.y + obj_size2.height)
            {
                if (obj_pos1.x + obj_size1.width >= obj_pos2.x && obj_pos1.x - 15 <= obj_pos2.x) {
                    return 4;
                }
                else if (obj_pos1.x <= obj_pos2.x + obj_size2.width && obj_pos1.x + obj_size1.width >= obj_pos2.x + obj_size2.width)
                {
                    return 2;
                }
            }
            return 1;
        }
    }
    return 0;
}

void Game::checkButton(sf::RenderTarget& window)
{
    if (sf::Joystick::isButtonPressed(0, 0))
    {
        text.setString("Button 0");
    }
    if (sf::Joystick::isButtonPressed(0, 1))
    {
        text.setString("Button 1");
    }
    else if (sf::Joystick::isButtonPressed(0, 2))
    {
        text.setString("Button 2");
    }
    else if (sf::Joystick::isButtonPressed(0, 3))
    {
        text.setString("Button 3");
    }
    else if (sf::Joystick::isButtonPressed(0, 4))
    {
        text.setString("Button 4");
    }
    else if (sf::Joystick::isButtonPressed(0, 5))
    {
        text.setString("Button 5");
    }
    else if (sf::Joystick::isButtonPressed(0, 6))
    {
        text.setString("Button 6");
    }
    else if (sf::Joystick::isButtonPressed(0, 7))
    {
        text.setString("Button 7");
    }
    else if (sf::Joystick::isButtonPressed(0, 8))
    {
        text.setString("Button 8");
    }
    else if (sf::Joystick::isButtonPressed(0, 9))
    {
        text.setString("Button 9");
    }
    else if (sf::Joystick::isButtonPressed(0, 10))
    {
        text.setString("Button 10");
    }
    else if (sf::Joystick::isButtonPressed(0, 11))
    {
        text.setString("Button 11");
    }
    else if (sf::Joystick::isButtonPressed(0, 12))
    {
        text.setString("Button 12");
    }
    else if (sf::Joystick::isButtonPressed(0, 13))
    {
        text.setString("Button 13");
    }
    window.draw(text);
}

void Game::PlayerInput(Player& player)
{
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
            player.SetShiftPressed(true);
        }
        else if (!player.IsJumping()) {
            player.SetShiftPressed(false);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1)) {
            player.SetJumping(true);
        }
        else
        {
            player.SetJumping(false);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) || sf::Joystick::isButtonPressed(0, 7)) {
            dir.x = 0.0f;
            if (!player.IsJumping())
            {
                player.SetGuard(true);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Joystick::isButtonPressed(0, 2)) {
            dir.x = 0.0f;
            if (!player.IsJumping())
            {
                player.atk = true;
            }
        }

        player.SetDirection(dir);

  
}

void Game::enemyPhysics(Player& fucker, sf::RenderTarget& window)
{
    for (int e = 0; e < enemy.size(); e++)
    {
        enemy[e]->SetDirection();
        int col = 0;
        sf::Vector2f enemyPos = { enemy[e]->GetPosition().x - enemy[e]->GetSize().width / 2,enemy[e]->GetPosition().y - enemy[e]->GetSize().height / 2 };
        if (e >= 0) { col = TestCollision(fucker.GetSize(), fucker.GetPosition(), enemy[e]->GetSize(), enemyPos); }
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
                newPos.x = enemyPos.x + enemy[e]->GetSize().width + 2;
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
        //Enemy with world
        for (int g = 0; g < ground.size(); g++)
        {
            ground[g].SetDirection();
            int col = 0;
            if (g != 0) { col = TestCollision(enemy[e]->GetSize(), enemy[e]->GetPosition(), ground[g].GetSize(), ground[g].GetPosition()); }

            if (col != 0)
            {
                sf::Vector2f newPos = enemy[e]->GetPosition();
                newPos.y = ground[g].GetPosition().y - enemy[e]->GetSize().height + 1;
                enemy[e]->validJump = true;
                enemy[e]->falling = false;
                //Slime behavior
                if (enemy[e]->enemyId == 1)
                {
                    if (newPos.x - enemy[e]->GetSize().width >= ground[g].getTileEnd() - 20)
                    {
                        enemy[e]->rightCollision();
                        newPos.x -= 20;
                        //col = 999;
                    }
                    else if (newPos.x - enemy[e]->GetSize().width <= ground[g].getTileStart() + 20)
                    {
                        enemy[e]->leftCollision();
                        newPos.x += 20;
                    }
                }
                //
                switch (col)
                {
                case 1:
                    break;
                case 2:
                    newPos.x = ground[g].GetPosition().x + ground[g].GetSize().width + 5;
                    newPos.y = enemy[e]->GetPosition().y;
                    enemy[e]->leftCollision();
                    break;
                case 3:
                    break;
                case 4:
                    newPos.x = ground[g].GetPosition().x - 5;
                    newPos.y = enemy[e]->GetPosition().y;
                    enemy[e]->rightCollision();
                    break;
                default:
                    break;
                }
                enemy[e]->setPosition(newPos);
            }
            ground[g].Update(dt);
            if (g > 1)
            {
                ground[g].Draw(window);
            }
        }

        enemy[e]->Update(dt);
        enemy[e]->Draw(window);
    }
}

//Control buttons
// 0 = Square, 1 = X, 2 = Circle, 3 = Traingle, 4 = L1, 5 = R1, 6 = L2, 7 = R2, 8 = Options, 9 = Start, 10 = L3, 11 = R3, 12 = PS, 13 = Pad
