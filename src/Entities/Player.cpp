#include "Entities/Player.h"

Player::Player(int id, std::shared_ptr<sf::Texture> texture, World &world) : Character(id, std::move(texture), world) {
    setSpeed(1.0f);
    setCanInteractWithObjects(true);

    // TODO: Rebalance attributes?
    setBaseAttribute(Attribute::HEALTH, 10);
    setCurrentAttribute(Attribute::HEALTH, 10);

    setBaseAttribute(Attribute::STRENGTH, 10);
    setCurrentAttribute(Attribute::STRENGTH, 10);

    setBaseAttribute(Attribute::DEXTERITY, 10);
    setCurrentAttribute(Attribute::DEXTERITY, 10);
}