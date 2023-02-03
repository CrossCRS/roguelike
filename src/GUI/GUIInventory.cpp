#include "GUI/GUIInventory.h"

#include "Constants.h"
#include "Entities/Player.h"
#include "Map/World.h"
#include "System/Inventory.h"
#include "System/Resources/ResourceManager.h"

#pragma warning(disable : 4244)

// TODO: Base GUI Panel class
GUIInventory::GUIInventory(World &_world, Inventory &_inventory) : world(_world), inventory(_inventory), opened(false), selected(0) {
    title.setFont(*world.getResourceManager().getFont("default"));
    title.setCharacterSize(32);

    text.setFont(*world.getResourceManager().getFont("default"));
    text.setCharacterSize(16);

    background.setFillColor(sf::Color::Black);
    background.setOutlineColor({ 150, 150, 150 });
    background.setOutlineThickness(1.0f);
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
        text << "\n";
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
        text.setPosition(static_cast<int>((Constants::GAME_WIDTH / 2.f) - (text.getLocalBounds().width / 2.f)), 100);

        background.setPosition(title.getPosition() - sf::Vector2(20.f, 10.f));
        float bg_width = std::max(text.getLocalBounds().width + 40.f, title.getLocalBounds().width + 40.f);
        float bg_height = std::max(128.f, text.getLocalBounds().height + title.getLocalBounds().height + 20.f);
        background.setSize(sf::Vector2f(bg_width, bg_height));
    }
}

void GUIInventory::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (opened) {
        target.draw(background, states);
        target.draw(title, states);
        target.draw(text, states);
    }
}