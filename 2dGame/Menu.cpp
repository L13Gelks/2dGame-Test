#include "Menu.h"
Menu::Menu(int width, int height)
{
    if (!font.loadFromFile("Font/arial.ttf"))
    {
        // error...
    }

    // select the font
    text[0].setFont(font); // font is a sf::Font
    // set the string to display
    text[0].setString("Inventory");
    // set the character size
    text[0].setCharacterSize(24); // in pixels, not points!
    // set the color
    text[0].setFillColor(sf::Color::Red);
    text[0].setPosition(sf::Vector2f(width/2 + (width/11) * 1,height / 13 ));

    text[1].setFont(font);
    text[1].setString("Stats    ");
    text[1].setCharacterSize(24);
    text[1].setFillColor(sf::Color::White);
    text[1].setPosition(sf::Vector2f(width/2 + (width / 9) * 2, height / 13));

    text[2].setFont(font);
    text[2].setString("Restart  ");
    text[2].setCharacterSize(24);
    text[2].setFillColor(sf::Color::White);
    text[2].setPosition(sf::Vector2f(width/2 + (width / 9) * 3, height / 13));
    
    texture.loadFromFile("sprite/menu/menu.png");
    sprite.setTexture(texture);
    sprite.setScale({ 0.7084,0.7084 });
    sprite.setPosition(0,0);
    selectedItem = 0;
    screenHeight = height;
    screenWidth = width;
}

void Menu::draw(sf::RenderTarget& rt)
{
    text[0].setPosition(sf::Vector2f((pos.x + (screenWidth / 2)) + (screenWidth / 11) * 1, screenHeight / 13));
    text[1].setPosition(sf::Vector2f((pos.x + (screenWidth / 2)) + (screenWidth / 9) * 2, screenHeight / 13));
    text[2].setPosition(sf::Vector2f((pos.x + (screenWidth / 2)) + (screenWidth / 8.5) * 3, screenHeight / 13));
    sprite.setPosition(pos);
    rt.draw(sprite);
    for (int i = 0; i < MAX_NUMBER_OPTIONS; i++)
    {
        rt.draw(text[i]);
    }
}

int Menu::getOption()
{
    return selectedItem;
}

void Menu::showStats(sf::RenderTarget& rt, Player& player)
{
    std::string info = "";
    std::stringstream sstream;
    int mult = 0.5f;
    int counter = 0;
        for (int i = 0; i < MAX_NUMBER_STATS; i++)
        {
            if (i >= 8) { mult = 1; }
            stats[i].setFont(font);
            sstream.str("");
            switch (i)
            {
            case 0:
                info = "Hp: ";
                sstream << player.getHealthPoints();
                sstream << "/";
                sstream << player.getMaxHealthPoints();
                info += sstream.str();
                stats[i].setString(info);
                break;
            case 1:
                info = "Stamina: ";
                sstream << player.getStaminaPoints();
                sstream << "/";
                sstream << player.getMaxStaminaPoints();
                info += sstream.str();
                stats[i].setString(info);
                break;
            case 2:
                info = "Mana: ";
                sstream << player.getManaPoints();
                sstream << "/";
                sstream << player.getMaxManaPoints();
                info += sstream.str();
                stats[i].setString(info);
                break;
            case 8:
                info = "Hp Regen: ";
                sstream << player.getHealthPointsRegen();
                info += sstream.str();
                info += "/s";
                stats[i].setString(info);
                break;
            case 9:
                info = "Sp Regen: ";
                sstream << player.getStaminaPointsRegen();
                info += sstream.str();
                info += "/s";
                stats[i].setString(info);
                break;
            case 10:
                info = "Mp Regen: ";
                sstream << player.getManaPointsRegen();
                info += sstream.str();
                info += "/s";
                stats[i].setString(info);
                break;
            default:
                stats[i].setString("Stat:");
                break;
            }
            stats[i].setCharacterSize(20);
            stats[i].setFillColor(sf::Color::White);
            stats[i].setPosition(sf::Vector2f((pos.x + (screenWidth / 2)) + (screenWidth / 4) * mult, screenHeight/2 + 21*counter));
            rt.draw(stats[i]);
            counter++;
            if (counter >= 8) { counter = 0; }
        }
}

void Menu::MoveUp()
{
    if(selectedItem - 1 >= 0)
    {
        text[selectedItem].setFillColor(sf::Color::White);
        selectedItem--;
        text[selectedItem].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown()
{
    if (selectedItem + 1 < MAX_NUMBER_OPTIONS)
    {
        text[selectedItem].setFillColor(sf::Color::White);
        selectedItem++;
        text[selectedItem].setFillColor(sf::Color::Red);
    }
}

void Menu::setPosition(sf::Vector2f& position)
{
    this->pos = position;
}
