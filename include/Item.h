#pragma once

#include "magic_enum.hpp"

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

class Character;

enum class ItemQuality {
    COMMON,
    RARE,
    LEGENDARY
};

enum class ItemSlot {
    NONE,
    RIGHT_HAND
};

enum class ItemFlag {
    NONE      = 0,
    EQUIPABLE = 1,
    USEABLE   = 1 << 1
};

enum class ItemProperty {
    DAMAGE
};

ItemFlag operator|(ItemFlag lhs, ItemFlag rhs);
ItemFlag operator&(ItemFlag lhs, ItemFlag rhs);

class Item {
public:
    explicit Item(int _id) :
        id(_id),
        texture(nullptr),
        equipped(false),
        flag(ItemFlag::NONE) {}

    bool isEquipable() const;
    bool isUsable() const;

    int getId() const;
    const std::string &getName() const;
    const std::string &getDescription() const;
    std::shared_ptr<sf::Texture> getTexture() const;
    bool isEquipped() const;
    const ItemQuality &getQuality() const;
    const ItemFlag &getFlag() const;
    const ItemSlot &getSlot() const;
    int getProperty(ItemProperty property) const;

    void setName(const std::string &_name);
    void setDescription(const std::string &_description);
    void setTexture(std::shared_ptr<sf::Texture> _texture);
    void setQuality(ItemQuality _quality);
    void setFlag(ItemFlag _flag);
    void setSlot(ItemSlot _slot);
    void setProperty(ItemProperty property, int value);

    void use(Character *user, Character *target);

private:
    int id;
    std::string name;
    std::string description;
    std::shared_ptr<sf::Texture> texture;

    bool equipped;

    ItemQuality quality;
    ItemFlag flag;
    ItemSlot slot;
    int properties[magic_enum::enum_count<ItemProperty>()];
};