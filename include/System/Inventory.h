#pragma once

#include "Item.h"

class Character;

class Inventory {
public:
    Inventory(Character &_owner, size_t _size) : owner(_owner), size(_size) {
        for (auto &i : equipped) {
            i = nullptr;
        }
    }

    size_t getItemCount() const;
    size_t getSize() const;
    Item &getItem(size_t pos);
    Item *getItemInSlot(ItemSlot slot);

    void setSize(size_t _size);
    bool equip(int id);
    bool unequip(int id);

    void addItem(std::unique_ptr<Item> item);

private:
    Character &owner;

    std::vector<std::unique_ptr<Item>> items;
    Item *equipped[magic_enum::enum_count<ItemSlot>()];

    size_t size;
};