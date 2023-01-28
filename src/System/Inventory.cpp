#include "System/Inventory.h"

size_t Inventory::getItemCount() const {
    return items.size();
}

size_t Inventory::getSize() const {
    return size;
}

void Inventory::setSize(size_t _size) {
    size = _size;
}

Item &Inventory::getItem(size_t pos) {
    return *items.at(pos).get();
}

Item *Inventory::getItemInSlot(ItemSlot slot) {
    return this->equipped[static_cast<int>(slot)];
}

bool Inventory::equip(int id) {
    for (const auto &item : this->items) {
        if (item->getId() == id) {
            equipped[static_cast<int>(item->getSlot())] = item.get();
            return true;
        }
    }
    return false;
}

bool Inventory::unequip(int id) {
    for (const auto &item : this->equipped) {
        if (item != nullptr && item->getId() == id) {
            equipped[static_cast<int>(item->getSlot())] = nullptr;
            return true;
        }
    }
    return false;
}

void Inventory::addItem(std::unique_ptr<Item> item) {
    (void)owner;
    items.push_back(std::move(item));
}