#pragma once

#include "Constants.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scenes.h"
#include "Scenes/SplashScene.h"
#include "System/Resources/ResourceManager.h"
#include "System/SceneManager.h"

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