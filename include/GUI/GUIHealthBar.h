#pragma once

#include "Utils/RichText.h"

#include <SFML/Graphics.hpp>

class Character;

class GUIHealthBar : public sf::Drawable, public sf::Transformable {
public:
    GUIHealthBar(Character &_character, bool _mini);

    void update();
    void setSize(const sf::Vector2f &_size);
    const sf::Vector2f &getSize();

private:
    Character &character;

    sf::Vector2f size;
    bool mini;

    sf::RectangleShape background;
    sf::RectangleShape bar;
    sfe::RichText text;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};