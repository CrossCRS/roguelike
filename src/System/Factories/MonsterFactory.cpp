#include "System/Factories/MonsterFactory.h"
#include "Map/World.h"

size_t MonsterFactory::loadDefinitions(const std::string &dataDir) {
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

std::unique_ptr<Monster> MonsterFactory::instantiate(const std::string &monsterName, World &world) {
    if (!monsterDefs.contains(monsterName)) {
        const auto message = "Monster '" + monsterName + "' is not loaded";
        spdlog::error(message);
        throw std::invalid_argument(message);
    }

    auto monster = std::make_unique<Monster>(currentId, world);
    auto &monsterDef = monsterDefs[monsterName];
    currentId++;

    // Set basic fields
    monster->setName(monsterDef["name"].get<std::string>());
    monster->setTexture(world.getResourceManager().getTexture(monsterDef["texture"].get<std::string>()));

    // Set attributes
    for (int i = 0; i < Attribute::LAST; i++) {
        auto attr = magic_enum::enum_cast<Attribute::Index>(i);
        if (!attr.has_value()) continue;

        auto attrString = magic_enum::enum_name(attr.value());
        monster->setBaseAttribute(attr.value(), monsterDef["attributes"][attrString].get<int>());
        monster->setCurrentAttribute(attr.value(), monsterDef["attributes"][attrString].get<int>());
    }

    // TODO: Set level, experience...

    return monster;
}

void MonsterFactory::loadDefinition(const std::string &name, const std::string &path) {
    std::ifstream def(path);

    if (!def.good()) {
        const auto message = "Couldn't load monster definition file '" + path + "'";
        spdlog::error(message);
        throw std::invalid_argument(message);
    }

    monsterDefs[name] = nlohmann::json::parse(def);
    spdlog::debug("Loaded monster definition for '{}'", name);

    def.close();
}