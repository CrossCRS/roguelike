#pragma once

#include <string>
#include <type_traits>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

enum class ItemQuality {
    COMMON,
    RARE,
    LEGENDARY,
    LAST
};

enum class ItemSlot {
    NONE,
    LAST
};

enum class ItemFlag {
    EQUIPABLE = 1,
    USEABLE   = 1 << 1,
};

ItemFlag operator|(ItemFlag lhs, ItemFlag rhs);
ItemFlag operator&(ItemFlag lhs, ItemFlag rhs);

class Item {
public:
    explicit Item(int _id) : id(_id), texture(nullptr) {}

    bool isEquipable() const;
    bool isUsable() const;

    int getId() const;
    const std::string &getName() const;
    const std::string &getDescription() const;
    std::shared_ptr<sf::Texture> getTexture() const;
    const ItemQuality &getQuality() const;
    const ItemFlag &getFlag() const;
    const ItemSlot &getSlot() const;

    void setName(const std::string &_name);
    void setDescription(const std::string &_description);
    void setTexture(std::shared_ptr<sf::Texture> _texture);
    void setQuality(ItemQuality _quality);
    void setFlag(ItemFlag _flag);
    void setSlot(ItemSlot _slot);

private:
    int id;
    std::string name;
    std::string description;
    std::shared_ptr<sf::Texture> texture;

    ItemQuality quality;
    ItemFlag flag;
    ItemSlot slot;
};