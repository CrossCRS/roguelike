#include "Game.h"

Game::Game() : window(sf::VideoMode(Constants::GAME_WIDTH, Constants::GAME_HEIGHT), Constants::GAME_NAME, sf::Style::Titlebar | sf::Style::Close) {
    window.setFramerateLimit(60);

    resourceManager = std::make_unique<ResourceManager>(Constants::GAME_DATA_DIR);

    sceneManager = std::make_unique<SceneManager>();
    sceneManager->addScene(SCENE_SPLASH, std::make_shared<SplashScene>(*sceneManager, *resourceManager, window));
    sceneManager->addScene(SCENE_GAME, std::make_shared<GameScene>(*sceneManager, *resourceManager, window));

    sceneManager->switchScene(SCENE_SPLASH);
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