#pragma once
#include <vector>

class MapGenerator {
public:
    MapGenerator() {}

    std::tuple<std::vector<char>, unsigned int, unsigned int> generate();

private:
    void generateCorridor(std::vector<char> &map, unsigned int mapWidth, unsigned int mapHeight);
    void generateRoom(std::vector<char> &map, unsigned int mapWidth, unsigned int mapHeight);
};