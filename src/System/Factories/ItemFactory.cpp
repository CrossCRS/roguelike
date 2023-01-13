#include "System/Factories/ItemFactory.h"

#include "Item.h"
#include "Map/World.h"
#include "System/Resources/ResourceManager.h"

#include <filesystem>
#include <fstream>
#include <magic_enum.hpp>

size_t ItemFactory::loadDefinitions(const std::string &dataDir) {
    size_t loaded = 0;
    for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(dataDir)) {
        if (dirEntry.is_regular_file() && dirEntry.path().extension() == ".json") {
            const auto &path = dirEntry.path();
            loadDefinition(path.filename().replace_extension("").string(), path.string());
            loaded++;
        }
    }
    return loaded;
}

std::unique_ptr<Item> ItemFactory::instantiate(const std::string &itemName, World &world) {
    if (!itemDefs.contains(itemName)) {
        const auto message = "Item '" + itemName + "' is not loaded";
        spdlog::error(message);
        throw std::invalid_argument(message);
    }

    auto item = std::make_unique<Item>(currentId);
    auto &itemDef = itemDefs[itemName];
    currentId++;

    // Load basic attributes
    item->setName(itemDef["name"].get<std::string>());
    item->setDescription(itemDef["description"].get<std::string>());
    item->setTexture(world.getResourceManager().getTexture(itemDef["texture"].get<std::string>()));
    item->setQuality(magic_enum::enum_cast<ItemQuality>(itemDef["quality"].get<std::string>()).value_or(ItemQuality::COMMON));
    item->setSlot(magic_enum::enum_cast<ItemSlot>(itemDef["slot"].get<std::string>()).value_or(ItemSlot::NONE));

    // Load flags
    for (auto const &flEntry : itemDef["flags"]) {
        auto newFlag = magic_enum::enum_cast<ItemFlag>(flEntry.get<std::string>());
        if (newFlag.has_value()) {
            item->setFlag(item->getFlag() | newFlag.value()); // Add a new flag
        }
    }

    return item;
}

void ItemFactory::loadDefinition(const std::string &name, const std::string &path) {
    std::ifstream def(path);

    if (!def.good()) {
        const auto message = "Couldn't load item definition file '" + path + "'";
        spdlog::error(message);
        throw std::invalid_argument(message);
    }

    itemDefs[name] = nlohmann::json::parse(def);
    spdlog::debug("Loaded item definition for '{}'", name);

    def.close();
}