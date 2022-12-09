#pragma once

#include "System/Resources/ResourceManager.h"

#include <filesystem>
#include <fstream>
#include <magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

class ItemFactory {
public:
    static size_t loadDefinitions(const std::string& dataDir);

    static std::unique_ptr<int> instantiate(const std::string& itemName);

private:
    inline static int currentId = 600000; // Item ids will start at 600000
    inline static std::unordered_map<std::string, nlohmann::json> itemDefs;

    static void loadDefinition(const std::string& name, const std::string& path);
};