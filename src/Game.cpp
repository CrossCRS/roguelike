#include "Game.h"

#include "Constants.h"
#include "Scenes/GameScene.h"
#include "Scenes/SplashScene.h"

Game::Game() : window(sf::VideoMode(Constants::GAME_WIDTH, Constants::GAME_HEIGHT), Constants::GAME_NAME, sf::Style::Titlebar | sf::Style::Close) {
    window.setFramerateLimit(60);

    resourceManager = std::make_unique<ResourceManager>(Constants::GAME_DATA_DIR);

    sceneManager = std::make_unique<SceneManager>();
    sceneManager->addScene(SceneIndex::SPLASH, std::make_unique<SplashScene>(*sceneManager, *resourceManager, window));
    sceneManager->addScene(SceneIndex::GAME, std::make_unique<GameScene>(*sceneManager, *resourceManager, window));

    sceneManager->switchScene(SceneIndex::SPLASH);
}

void Game::run() {
    sf::Clock clockFrame;
    sf::Clock clockTotal;

    while (window.isOpen()) {
        sf::Event event {};

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    sceneManager->handleInput(event.key.code);
                    break;
                default:
                    break;
            }
        }

        sf::Time delta = clockFrame.restart();

        sceneManager->update(delta.asSeconds(), clockTotal.getElapsedTime().asSeconds());
        sceneManager->draw();
        window.display();
    }
}