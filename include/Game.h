#pragma once

#include "System/SceneManager.h"
#include "System/Resources/ResourceManager.h"

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();

    void run();

private:
    sf::RenderWindow window;

    std::unique_ptr<ResourceManager> resourceManager;
    std::unique_ptr<SceneManager> sceneManager;
};