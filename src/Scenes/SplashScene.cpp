#include "Scenes/SplashScene.h"

#include "Constants.h"
#include "System/Resources/ResourceManager.h"
#include "System/SceneManager.h"

SplashScene::SplashScene(SceneManager &sceneManager, ResourceManager &resourceManager, sf::RenderWindow &window) :
	sceneManager(sceneManager), resourceManager(resourceManager), window(window), loadResourcesThreadFinished(false), loaded(false) { }

void SplashScene::loadResourcesThreadFunc() {
	resourceManager.loadResources();
	loadResourcesThreadFinished = true;
}

void SplashScene::onLoad() {
	window.setView(window.getDefaultView());

	splash_logo.setTexture(*resourceManager.getTexture("splash_logo"));
	splash_logo.setOrigin(splash_logo.getGlobalBounds().width / 2, splash_logo.getGlobalBounds().height / 2);
	splash_logo.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

	text_gamename.setFont(*resourceManager.getFont("default"));
	text_gamename.setCharacterSize(64);
	text_gamename.setPosition(0.f, splash_logo.getGlobalBounds().top - 150.f);
	text_gamename.setFillColor(sf::Color::White);
	text_gamename.setString(Constants::GAME_NAME);
	centerText(text_gamename);

	text_splash.setFont(*resourceManager.getFont("default"));
	text_splash.setCharacterSize(32);
	text_splash.setPosition(0.f, splash_logo.getGlobalBounds().top + splash_logo.getGlobalBounds().height + 32.f);
	text_splash.setFillColor(sf::Color::White);
	text_splash.setString("Loading stuff...");
	centerText(text_splash);

    text_copy.setFont(*resourceManager.getFont("default"));
    text_copy.setCharacterSize(16);
    text_copy.setFillColor(sf::Color(64, 64, 64));
    text_copy.setString("(c) Norbert Budzynski 2022");
    text_copy.setPosition(6.f, Constants::GAME_HEIGHT - text_copy.getGlobalBounds().height - 10.f);
	
	loadResourcesThread = std::thread([this] { this->loadResourcesThreadFunc(); });
}

void SplashScene::handleInput(sf::Keyboard::Key key) {
	switch (key) {
		case sf::Keyboard::Enter:
			if (loaded) sceneManager.switchScene(Scene::GAME);
			break;
		case sf::Keyboard::Escape:
			window.close();
			break;
		default:
			break;
	}
}

void SplashScene::update(float, float elapsed) {
	if (loadResourcesThreadFinished) {
		loadResourcesThread.join();
		loadResourcesThreadFinished = false;

		loaded = true;
		text_splash.setString("Press Enter to start game!");
		centerText(text_splash);
	}

	const float scale = 0.3f * std::sin(elapsed * 4) + 1;
	const float angle = 30.f * std::sin(elapsed * 2);
	splash_logo.setScale(scale, scale);
	splash_logo.setRotation(angle);
}

void SplashScene::draw() {
	window.clear();

	window.draw(text_gamename);
	window.draw(text_splash);
    window.draw(text_copy);
	window.draw(splash_logo);
}

void SplashScene::centerText(sf::Text &text) {
	text.setPosition(sf::Vector2f((window.getSize().x / 2) - (text.getGlobalBounds().width / 2), text.getPosition().y));
}