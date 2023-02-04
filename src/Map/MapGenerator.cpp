#include "Map/MapGenerator.h"

#include <effolkronium/random.hpp>
#include <queue>

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

std::tuple<std::vector<char>, unsigned int, unsigned int, sf::Vector2i> MapGenerator::generate() {
    float walkable = 0.f;

    std::vector<char> map;
    unsigned int width;
    unsigned int height;
    sf::Vector2i spawnPos;

    do {
        width = Random::get<unsigned int>(MIN_SIZE, MAX_SIZE);
        height = Random::get<unsigned int>(MIN_SIZE, MAX_SIZE);

        map.clear();
        map.resize(width * height, TILE_WALL);

        // Corridors
        auto corridorCount = Random::get<unsigned int>(MIN_CORRIDORS, MAX_CORRIDORS);
        for (unsigned int i = 0; i < corridorCount; i++) {
            generateCorridor(map, width, height);
        }

        // Rooms
        auto roomCount = Random::get<unsigned int>(MIN_ROOMS, MAX_ROOMS);
        for (unsigned int i = 0; i < roomCount; i++) {
            generateRoom(map, width, height);
        }

        // TODO: Add doors

        // Pick a spawn point
        unsigned int x, y;
        do {
            x = Random::get<unsigned int>(0, width - 1);
            y = Random::get<unsigned int>(0, height - 1);
        } while (map[x + y * width] != TILE_FLOOR);
        spawnPos = { static_cast<int>(x), static_cast<int>(y) };

        walkable = calculateWalkablePercent(map, width, height, spawnPos);
    } while (walkable < 0.50f || walkable > 0.75f);

    return { map, width, height, spawnPos };
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

float MapGenerator::calculateWalkablePercent(const std::vector<char> &map, unsigned int mapWidth, unsigned int mapHeight, sf::Vector2i pos) {
    std::vector<char> mapCopy(map);

    std::queue<sf::Vector2i> q;
    q.push(pos);

    size_t walkable = 0;

    while (!q.empty()) {
        sf::Vector2i curPos = q.front();
        q.pop();
        if ((curPos.x < static_cast<int>(mapWidth) - 1 && curPos.y < static_cast<int>(mapHeight) - 1) &&
                (curPos.x >= 0 && curPos.y >= 0) &&
                mapCopy[curPos.x + curPos.y * mapWidth] == TILE_FLOOR || mapCopy[curPos.x + curPos.y * mapWidth] == TILE_DOOR) {
            walkable++;
            mapCopy[curPos.x + curPos.y * mapWidth] = TILE_WALL;
            q.push(curPos + sf::Vector2i(-1, 0));
            q.push(curPos + sf::Vector2i(1, 0));
            q.push(curPos + sf::Vector2i(0, -1));
            q.push(curPos + sf::Vector2i(0, 1));
        }
    }

    return static_cast<float>(walkable) / static_cast<float>(map.size());
}
