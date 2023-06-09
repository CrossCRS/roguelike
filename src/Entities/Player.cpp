#include "Entities/Player.h"

Player::Player(int id, std::shared_ptr<sf::Texture> texture, World &world) : Character(id, std::move(texture), world) {
    setSpeed(1.0f);
    setCanInteractWithObjects(true);

    // TODO: Rebalance attributes?
    setBaseAttribute(AttributeIndex::HEALTH, 10);
    setCurrentAttribute(AttributeIndex::HEALTH, 10);

    setBaseAttribute(AttributeIndex::STRENGTH, 1);
    setCurrentAttribute(AttributeIndex::STRENGTH, 1);

    setBaseAttribute(AttributeIndex::DEXTERITY, 1);
    setCurrentAttribute(AttributeIndex::DEXTERITY, 1);
}

bool Player::isPlayer() const {
    return true;
}