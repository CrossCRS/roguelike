#pragma once
#include "SFML/System/Vector2.hpp"

#include <vector>

class MapGenerator {
public:
    MapGenerator() {}

    std::tuple<std::vector<char>, unsigned int, unsigned int, sf::Vector2i> generate();

private:
    void generateCorridor(std::vector<char> &map, unsigned int mapWidth, unsigned int mapHeight);
    void generateRoom(std::vector<char> &map, unsigned int mapWidth, unsigned int mapHeight);

    float calculateWalkablePercent(const std::vector<char> &map, unsigned int mapWidth, unsigned int mapHeight, sf::Vector2i pos);
};