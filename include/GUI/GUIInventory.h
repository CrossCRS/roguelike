#pragma once

#include "Utils/RichText.h"

#include <SFML/Graphics.hpp>

class Inventory;
class World;

class GUIInventory : public sf::Drawable {
public:
    GUIInventory(World &_world, Inventory &_inventory);

    void handleInput(sf::Keyboard::Key key);
    void open();

    bool isOpened();

    void update();

private:
    World &world;
    Inventory &inventory;

    bool opened;
    size_t selected;

    sfe::RichText title;
    sfe::RichText text;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};