#include "Hud.h"

Hud::Hud(int width, int height)
{
    if (!font.loadFromFile("Font/arial.ttf"))
    {
        // error...
    }

    stats[0].setFont(font);
    stats[0].setString("");
    stats[0].setCharacterSize(15);
    stats[0].setFillColor(sf::Color::White);

    stats[1].setFont(font);
    stats[1].setString("");
    stats[1].setCharacterSize(15);
    stats[1].setFillColor(sf::Color::White);

    stats[2].setFont(font);
    stats[2].setString("");
    stats[2].setCharacterSize(15);
    stats[2].setFillColor(sf::Color::White);

    hpBar.setSize(sf::Vector2f(300.0f, 10.f));
    hpBar.setFillColor(sf::Color::Red);
    hpBarBorder.setSize(sf::Vector2f(300.0f, 10.f));
    hpBarBorder.setFillColor(sf::Color::Black);
    hpBarBorder.setOutlineThickness(2.f);
    hpBarBorder.setOutlineColor(sf::Color::Red);

    spBar.setSize(sf::Vector2f(200.0f, 10.f));
    spBar.setFillColor(sf::Color::Green);
    spBarBorder.setSize(sf::Vector2f(200.0f, 10.f));
    spBarBorder.setFillColor(sf::Color::Black);
    spBarBorder.setOutlineThickness(2.f);
    spBarBorder.setOutlineColor(sf::Color::Green);
}

void Hud::draw(sf::RenderTarget& rt)
{
    outline.setPosition(pos.x + MaxRadius, pos.y + MaxRadius);
    outline.setRadius(MaxRadius);
    outline.setOutlineThickness(2.f);
    outline.setFillColor(sf::Color::Black);
    outline.setOutlineColor(sf::Color(250, 250, 250));
    inside.setPosition((pos.x + MaxRadius) + (MaxRadius - radius), (pos.y + MaxRadius) + (MaxRadius - radius));
    inside.setRadius(radius);
    inside.setFillColor(sf::Color::Blue);

    hpBar.setSize(sf::Vector2f(Hbar, 10.f));
    hpBar.setPosition(pos.x + MaxRadius * 3, outline.getPosition().y + MaxRadius / 2);
    hpBarBorder.setPosition(pos.x + MaxRadius * 3, outline.getPosition().y + MaxRadius / 2);

    spBar.setSize(sf::Vector2f(Sbar, 10.f));
    spBar.setPosition(pos.x + MaxRadius * 3, (outline.getPosition().y + MaxRadius / 2) + 40.0f);
    spBarBorder.setPosition(pos.x + MaxRadius * 3, (outline.getPosition().y + MaxRadius / 2) + 40.0f);
   

    rt.draw(outline);
    rt.draw(inside);
    rt.draw(hpBarBorder);
    rt.draw(hpBar);
    rt.draw(spBarBorder);
    rt.draw(spBar);


    stats[0].setString(std::to_string(HealhPoints));
    stats[0].setPosition(pos.x + MaxRadius * 3, (outline.getPosition().y + MaxRadius / 2) - 20.0f);
    stats[1].setString(std::to_string(ManaPoints));
    stats[1].setPosition(pos.x + MaxRadius * 1.75f, pos.y + MaxRadius * 1.75f);
    stats[2].setString(std::to_string(StaminaPoints));
    stats[2].setPosition(pos.x + MaxRadius * 3, (outline.getPosition().y + MaxRadius / 2) + 20.0f);
    rt.draw(stats[0]);
    rt.draw(stats[1]);
    rt.draw(stats[2]);
}

void Hud::setStats(Player& player)
{
    ManaPoints = player.getManaPoints();
    radius = MaxRadius;
    radius *= (ManaPoints / player.getMaxManaPoints());

    HealhPoints = player.getHealthPoints();
    Hbar = 300.0f;
    Hbar *= (HealhPoints / player.getMaxHealthPoints());

    StaminaPoints = player.getStaminaPoints();
    Sbar = 200.0f;
    Sbar *= (StaminaPoints / player.getMaxStaminaPoints());
}

void Hud::setPosition(sf::Vector2f& position)
{
	this->pos = position;
}
