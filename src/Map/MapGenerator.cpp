#include "Map/MapGenerator.h"

#include "effolkronium/random.hpp"

using Random = effolkronium::random_static;

constexpr int MIN_SIZE = 80;
constexpr int MAX_SIZE = 140;

constexpr int MIN_ROOM_SIZE = 5;
constexpr int MAX_ROOM_SIZE = 15;
constexpr int MIN_CORRIDOR_SIZE = 15;
constexpr int MAX_CORRIDOR_SIZE = 25;

constexpr int MIN_ROOMS = 30;
constexpr int MAX_ROOMS = 55;
constexpr int MIN_CORRIDORS = 50;
constexpr int MAX_CORRIDORS = 80;

// TODO: Move somewhere else, use enums?
constexpr char TILE_FLOOR = '-';
constexpr char TILE_WALL = '#';
constexpr char TILE_DOOR = 'D';

std::tuple<std::vector<char>, unsigned int, unsigned int> MapGenerator::generate() {
    std::vector<char> map;

    auto width = Random::get<unsigned int>(MIN_SIZE, MAX_SIZE);
    auto height = Random::get<unsigned int>(MIN_SIZE, MAX_SIZE);
    
    map.resize(width * height, TILE_WALL);

    auto corridorCount = Random::get<unsigned int>(MIN_CORRIDORS, MAX_CORRIDORS);
    for (unsigned int i = 0; i < corridorCount; i++) {
        generateCorridor(map, width, height);
    }

    auto roomCount = Random::get<unsigned int>(MIN_ROOMS, MAX_ROOMS);
    for (unsigned int i = 0; i < roomCount; i++) {
        generateRoom(map, width, height);
    }

    return { map, width, height };
}

void MapGenerator::generateCorridor(std::vector<char> &map, unsigned int mapWidth, unsigned int mapHeight) {
    auto horizontal = Random::get<bool>(0.5f);
    auto size = Random::get<unsigned int>(MIN_CORRIDOR_SIZE, MAX_CORRIDOR_SIZE);
    auto width = horizontal ? 1 : size;
    auto height = horizontal ? size : 1;
    auto startX = Random::get<unsigned int>(1, mapWidth - width - 2);
    auto startY = Random::get<unsigned int>(1, mapHeight - height - 2);

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            map[(i + startX) + (j + startY) * mapWidth] = TILE_FLOOR;
        }
    }
}

void MapGenerator::generateRoom(std::vector<char> &map, unsigned int mapWidth, unsigned int mapHeight) {
    auto width = Random::get<unsigned int>(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
    auto height = Random::get<unsigned int>(MIN_ROOM_SIZE, MAX_ROOM_SIZE);
    auto startX = Random::get<unsigned int>(1, mapWidth - width - 2);
    auto startY = Random::get<unsigned int>(1, mapHeight - height - 2);

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            map[(i + startX) + (j + startY) * mapWidth] = TILE_FLOOR;
        }
    }
}