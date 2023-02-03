#include "GUI/GUICharacterScreen.h"

#include "Constants.h"
#include "Entities/Player.h"
#include "Map/World.h"
#include "System/Resources/ResourceManager.h"

#pragma warning(disable : 4244)

GUICharacterScreen::GUICharacterScreen(World &_world, Player &_player) : world(_world), player(_player), opened(false) {
    title.setFont(*world.getResourceManager().getFont("default"));
    title.setCharacterSize(32);

    text.setFont(*world.getResourceManager().getFont("default"));
    text.setCharacterSize(16);

    background.setFillColor(sf::Color::Black);
    background.setOutlineColor({ 150, 150, 150 });
    background.setOutlineThickness(1.0f);
}

void GUICharacterScreen::handleInput(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::C:
        case sf::Keyboard::Escape:
            opened = false;
            break;
        default:
            break;
    }
}

void GUICharacterScreen::open() {
    opened = true;
}

bool GUICharacterScreen::isOpened() {
    return opened;
}

void GUICharacterScreen::update() {
    if (opened) {
        title.clear();
        title << "CHARACTER";
        title.setPosition((Constants::GAME_WIDTH / 2.f) - (title.getLocalBounds().width / 2.f), 64.f);

        text.clear();
        text << "\n";

        // TODO: :)
        text << sf::Color(255, 255, 255) << "Level: 1\nExp.: 0/123456789\nAttr. points: 0\n\n";

        text << sf::Color(255, 255, 255) << "ATTRIBUTES\n";
        for (auto const &[attr, attrString] : magic_enum::enum_entries<AttributeIndex>()) {
            auto name = std::string(attrString);
            for (auto &c : name) c = tolower(c);
            name[0] = toupper(name[0]);
            text << sf::Color(150, 150, 150) << "  " << name << ": " << std::to_string(player.getCurrentAttribute(attr)) << "/" << std::to_string(player.getBaseAttribute(attr)) << "\n";
        }

        text.setPosition(static_cast<int>((Constants::GAME_WIDTH / 2.f) - (text.getLocalBounds().width / 2.f)), 100);

        background.setPosition(title.getPosition() - sf::Vector2(20.f, 10.f));
        float bg_width = std::max(text.getLocalBounds().width + 40.f, title.getLocalBounds().width + 40.f);
        float bg_height = std::max(128.f, text.getLocalBounds().height + title.getLocalBounds().height + 20.f);
        background.setSize(sf::Vector2f(bg_width, bg_height));
    }
}

void GUICharacterScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (opened) {
        target.draw(background, states);
        target.draw(title, states);
        target.draw(text, states);
    }
}