#include "Item.h"

#include "Entities/Character.h"

ItemFlag operator|(ItemFlag lhs, ItemFlag rhs) {
    return static_cast<ItemFlag>(static_cast<std::underlying_type_t<ItemFlag>>(lhs) | static_cast<std::underlying_type_t<ItemFlag>>(rhs));
}

ItemFlag operator&(ItemFlag lhs, ItemFlag rhs) {
    return static_cast<ItemFlag>(static_cast<std::underlying_type_t<ItemFlag>>(lhs) & static_cast<std::underlying_type_t<ItemFlag>>(rhs));
}

bool Item::isEquipable() const {
    return (this->flag & ItemFlag::EQUIPABLE) == ItemFlag::EQUIPABLE;
}

bool Item::isUsable() const {
    return (this->flag & ItemFlag::USEABLE) == ItemFlag::USEABLE;
}

int Item::getId() const {
    return this->id;
}

const std::string &Item::getName() const {
    return this->name;
}

const std::string &Item::getDescription() const {
    return this->description;
}

std::shared_ptr<sf::Texture> Item::getTexture() const {
    return this->texture;
}

bool Item::isEquipped() const {
    return this->equipped;
}

const ItemQuality &Item::getQuality() const {
    return this->quality;
}

const ItemFlag &Item::getFlag() const {
    return this->flag;
}

const ItemSlot &Item::getSlot() const {
    return this->slot;
}

int Item::getProperty(ItemProperty property) const {
    return this->properties[static_cast<int>(property)];
}

void Item::setName(const std::string &_name) {
    this->name = _name;
}

void Item::setDescription(const std::string &_description) {
    this->description = _description;
}

void Item::setTexture(std::shared_ptr<sf::Texture> _texture) {
    this->texture = std::move(_texture);
}

void Item::setQuality(ItemQuality _quality) {
    this->quality = _quality;
}

void Item::setFlag(ItemFlag _flag) {
    this->flag = _flag;
}

void Item::setSlot(ItemSlot _slot) {
    this->slot = _slot;
}

void Item::setProperty(ItemProperty property, int value) {
    this->properties[static_cast<int>(property)] = value;
}

void Item::use(Character *user, Character *target) {
    // Equipping
    if (this->isEquipable() && user->getId() == target->getId()) {
        if (this->isEquipped()) {
            if (target->getInventory().unequip(this->getId()))
                this->equipped = false;
        } else {
            if (target->getInventory().equip(this->getId()))
                this->equipped = true;
        }
    }
}
