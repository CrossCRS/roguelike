#pragma once

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

class Monster;
class World;

class MonsterFactory {
public:
    static size_t loadDefinitions(const std::string &dataDir);

    static std::unique_ptr<Monster> instantiate(const std::string &monsterName, World &world);

private:
    inline static int currentId = 10000; // Monster ids will start at 10000
    inline static std::unordered_map<std::string, nlohmann::json> monsterDefs;

    static void loadDefinition(const std::string &name, const std::string &path);
};