#include "GUI/GUIInventory.h"

#include "Constants.h"
#include "Entities/Player.h"
#include "Map/World.h"
#include "System/Inventory.h"
#include "System/Resources/ResourceManager.h"

GUIInventory::GUIInventory(World &_world, Inventory &_inventory) : world(_world), inventory(_inventory), opened(false), selected(0) {
    title.setFont(*world.getResourceManager().getFont("default"));
    title.setCharacterSize(32);

    text.setFont(*world.getResourceManager().getFont("default"));
    text.setCharacterSize(16);
}

void GUIInventory::handleInput(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Up:
            if (selected <= 0) {
                selected = inventory.getItemCount() - 1;
            } else {
                selected--;
            }
            break;
        case sf::Keyboard::Down:
            if (selected >= inventory.getItemCount() - 1) {
                selected = 0;
            } else {
                selected++;
            }
            break;
        case sf::Keyboard::Enter:
            inventory.getItem(selected).use(world.getPlayer(), world.getPlayer());
            break;
        case sf::Keyboard::D:
            // DROP?
            break;
        case sf::Keyboard::I:
        case sf::Keyboard::Escape:
            opened = false;
            break;
        default:
            break;
    }
}

void GUIInventory::open() {
    opened = true;
}

bool GUIInventory::isOpened() {
    return opened;
}

void GUIInventory::update() {
    if (opened) {
        title.clear();
        title << "INVENTORY [" << std::to_string(inventory.getItemCount()) << "/" << std::to_string(inventory.getSize()) << "]";
        title.setPosition((Constants::GAME_WIDTH / 2.f) - (title.getLocalBounds().width / 2.f), 64.f);

        text.clear();
        for (size_t i = 0; i < inventory.getItemCount(); i++) {
            Item &item = inventory.getItem(i);
            if (i == selected) {
                text << sf::Color(255, 255, 255);
            } else {
                text << sf::Color(150, 150, 150);
            }

            // Item text
            text << item.getName();

            if (item.isEquipped())
                text << " -E-";

            text << "\n";
        }
        text.setPosition((Constants::GAME_WIDTH / 2.f) - (text.getLocalBounds().width / 2.f), 100.f);
    }
}

void GUIInventory::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (opened) {
        target.draw(title, states);
        target.draw(text, states);
    }
}