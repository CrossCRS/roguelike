#pragma once

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

ItemFlag operator|(ItemFlag lhs, ItemFlag rhs) {
    return static_cast<ItemFlag>(static_cast<std::underlying_type_t<ItemFlag>>(lhs) | static_cast<std::underlying_type_t<ItemFlag>>(rhs));
}

ItemFlag operator&(ItemFlag lhs, ItemFlag rhs) {
    return static_cast<ItemFlag>(static_cast<std::underlying_type_t<ItemFlag>>(lhs) & static_cast<std::underlying_type_t<ItemFlag>>(rhs));
}

class Item {
public:
    Item();

    bool isEquipable() const;
    bool isUsable() const;

    ItemQuality getQuality() const;
    ItemFlag getFlag() const;
    ItemSlot getSlot() const;

    void setQuality(ItemQuality _quality);
    void setFlag(ItemFlag _flag);
    void setSlot(ItemSlot _slot);

private:
    std::string name;
    std::string description;

    ItemQuality quality;
    ItemFlag flag;
    ItemSlot slot;
};