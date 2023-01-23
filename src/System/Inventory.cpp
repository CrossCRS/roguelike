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

void Inventory::addItem(std::unique_ptr<Item> item) {
    (void)owner;
    items.push_back(std::move(item));
}