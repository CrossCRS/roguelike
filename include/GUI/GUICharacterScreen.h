#pragma once

#include "Utils/RichText.h"

#include <SFML/Graphics.hpp>

class Player;
class World;

class GUICharacterScreen : public sf::Drawable {
public:
    GUICharacterScreen(World &_world, Player &_player);

    void handleInput(sf::Keyboard::Key key);
    void open();

    bool isOpened();

    void update();

private:
    World &world;
    Player &player;

    bool opened;

    sf::RectangleShape background;
    sfe::RichText title;
    sfe::RichText text;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};