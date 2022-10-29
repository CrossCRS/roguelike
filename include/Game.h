#pragma once

#include "Constants.h"
#include "Scenes/GameScene.h"
#include "Scenes/SplashScene.h"
#include "Scenes/Scenes.h"
#include "System/SceneManager.h"
#include "System/ResourceManager.h"

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();

    void run();

private:
    sf::RenderWindow window;

    std::unique_ptr<ResourceManager> resourceManager;
    std::unique_ptr<SceneManager> sceneManager;

    void update();
    void processTurn();
    void handleInput(sf::Keyboard::Key key);
    void draw();
};