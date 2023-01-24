#include "GUI/GUIInventory.h"

#include "Constants.h"
#include "System/Inventory.h"
#include "System/Resources/ResourceManager.h"

GUIInventory::GUIInventory(ResourceManager &resourceManager, Inventory &_inventory) : inventory(_inventory), opened(false), selected(0) {
    title.setFont(*resourceManager.getFont("default"));
    title.setCharacterSize(24);

    text.setFont(*resourceManager.getFont("default"));
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
            // USE
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
        title << sf::Text::Bold << "INVENTORY [" << std::to_string(inventory.getItemCount()) << "/" << std::to_string(inventory.getSize()) << "]";
        title.setPosition((Constants::GAME_WIDTH / 2) - (title.getLocalBounds().width / 2), 64);

        text.clear();
        for (size_t i = 0; i < inventory.getItemCount(); i++) {
            Item &item = inventory.getItem(i);
            if (i == selected) {
                text << sf::Color(255, 255, 255) << sf::Text::Bold;
            } else {
                text << sf::Color(180, 180, 180) << sf::Text::Regular;
            }
            text << item.getName() << "\n";
        }
        text.setPosition((Constants::GAME_WIDTH / 2) - (text.getLocalBounds().width / 2), 100);
    }
}

void GUIInventory::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (opened) {
        target.draw(title, states);
        target.draw(text, states);
    }
}