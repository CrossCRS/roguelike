#include "Item.h"

ItemFlag operator|(ItemFlag lhs, ItemFlag rhs) {
    return static_cast<ItemFlag>(static_cast<std::underlying_type_t<ItemFlag>>(lhs) | static_cast<std::underlying_type_t<ItemFlag>>(rhs));
}

ItemFlag operator&(ItemFlag lhs, ItemFlag rhs) {
    return static_cast<ItemFlag>(static_cast<std::underlying_type_t<ItemFlag>>(lhs) & static_cast<std::underlying_type_t<ItemFlag>>(rhs));
}

bool Item::isEquipable() const {
    return (flag & ItemFlag::EQUIPABLE) == ItemFlag::EQUIPABLE;
}

bool Item::isUsable() const {
    return (flag & ItemFlag::USEABLE) == ItemFlag::USEABLE;
}

int Item::getId() const {
    return id;
}

const std::string &Item::getName() const {
    return name;
}

const std::string &Item::getDescription() const {
    return description;
}

std::shared_ptr<sf::Texture> Item::getTexture() const {
    return texture;
}

const ItemQuality &Item::getQuality() const {
    return quality;
}

const ItemFlag &Item::getFlag() const {
    return flag;
}

const ItemSlot &Item::getSlot() const {
    return slot;
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