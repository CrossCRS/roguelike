#include "GUI/GUIHealthBar.h"

#include "Entities/Character.h"
#include "Map/World.h"
#include "System/Resources/ResourceManager.h"

#pragma warning(disable : 4244)

GUIHealthBar::GUIHealthBar(Character &_character, bool _mini) : character(_character), size({ 128, 16 }), mini(_mini) {
    text.setFont(*character.getWorld().getResourceManager().getFont("default"));
    text.setCharacterSize(16);

    if (mini) {
        size = { 32, 4 };
    }

    background.setFillColor(sf::Color::Black);
    background.setOutlineColor({ 150, 150, 150 });
    background.setOutlineThickness(1.0f);
    background.setSize(size);

    bar.setSize(background.getSize() - sf::Vector2f(2.f, 2.f));
    bar.setFillColor(sf::Color(220, 50, 30));
}

void GUIHealthBar::update() {
    background.setPosition(this->getPosition());
    bar.setPosition(this->getPosition() + sf::Vector2f(1.f, 1.f));

    const float healthPercentage = (static_cast<float>(character.getCurrentAttribute(AttributeIndex::HEALTH)) / static_cast<float>(character.getBaseAttribute(AttributeIndex::HEALTH)));
    bar.setSize(sf::Vector2f((background.getSize().x - 2.f) * healthPercentage, background.getSize().y - 2.f));

    if (!mini) {
        text.clear();
        text << std::to_string(character.getCurrentAttribute(AttributeIndex::HEALTH)) << "/" << std::to_string(character.getBaseAttribute(AttributeIndex::HEALTH));
        text.setPosition(static_cast<int>(this->getPosition().x + (this->getSize().x / 2) - (text.getLocalBounds().width / 2)), static_cast<int>(this->getPosition().y - this->getSize().y - 6));
    }
}

void GUIHealthBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(bar, states);
    if (!mini)
        target.draw(text, states);
}

const sf::Vector2f &GUIHealthBar::getSize() {
    return size;
}

void GUIHealthBar::setSize(const sf::Vector2f &_size) {
    this->size = _size;
    background.setSize(this->size);
    bar.setSize(background.getSize() - sf::Vector2f(2.f, 2.f));
}
