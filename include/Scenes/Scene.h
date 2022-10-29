#pragma once

#include <SFML/Graphics.hpp>

class Scene {
public:
	virtual ~Scene() = default;

	virtual void onCreate() {}; // One time only
	virtual void onDestroy() {}; // One time only

	virtual void onLoad() {}; // Everytime scene is activated
	virtual void onUnload() {}; // Everytime scene is deactivated

	virtual void handleInput(sf::Keyboard::Key key) = 0;
	virtual void update(float delta, float elapsed) = 0;
	virtual void draw() = 0;
};