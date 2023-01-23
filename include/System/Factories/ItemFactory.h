#pragma once

#include <nlohmann/json.hpp>

class Item;
class World;

class ItemFactory {
public:
    static size_t loadDefinitions(const std::string& dataDir);

    static std::unique_ptr<Item> instantiate(const std::string& itemName, World &world);

private:
    inline static int currentId = 600000; // Item ids will start at 600000
    inline static std::unordered_map<std::string, nlohmann::json> itemDefs;

    static void loadDefinition(const std::string& name, const std::string& path);
};