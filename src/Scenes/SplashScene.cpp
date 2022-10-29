#include "Scenes/SplashScene.h"

SplashScene::SplashScene(SceneManager &sceneManager, ResourceManager &resourceManager, sf::RenderWindow &window) :
	sceneManager(sceneManager), resourceManager(resourceManager), window(window), loaded(false) { }

void SplashScene::onLoad() {
	window.setView(window.getDefaultView());

	resourceManager.loadEssentialResources();

	splash_logo.setTexture(*resourceManager.getTexture("splash_logo"));
	splash_logo.setOrigin(splash_logo.getGlobalBounds().width / 2, splash_logo.getGlobalBounds().height / 2);
	splash_logo.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

	text_splash.setFont(*resourceManager.getFont("default"));
	text_splash.setCharacterSize(32);
	text_splash.setPosition(0.f, 400.f);
	text_splash.setFillColor(sf::Color::White);
	text_splash.setString("Loading stuff...");
	centerText();

	resourceManager.loadResources();

	loaded = true;

	text_splash.setString("Press Enter to start game!");
	centerText();
}

void SplashScene::handleInput(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Enter:
		if (loaded) sceneManager.switchScene(SCENE_GAME);
		break;
	default:
		break;
	}
}

void SplashScene::update(float, float elapsed) {
	const float scale = 0.3f * std::sin(elapsed * 4) + 1;
	const float angle = 15.f - 30.f * std::sin(elapsed * 2) - 15.f;
	splash_logo.setScale(scale, scale);
	splash_logo.setRotation(angle);
}

void SplashScene::draw() {
	window.clear();

	window.draw(text_splash);
	window.draw(splash_logo);
}

void SplashScene::centerText() {
	text_splash.setPosition(sf::Vector2f((window.getSize().x / 2) - (text_splash.getGlobalBounds().width / 2), 
											splash_logo.getGlobalBounds().top + splash_logo.getGlobalBounds().height + 32.f));
}