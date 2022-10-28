#include "Entities/Entity.h"

Entity::Entity(int id, const std::string &textureName, ResourceManager &resourceManager)
        : id(id), resourceManager(resourceManager) {
    texture = resourceManager.getTexture(textureName);
    vertices.setPrimitiveType(sf::Triangles);
    vertices.resize(6);

    vertices[0].position = sf::Vector2f(0.f, 0.f);
    vertices[1].position = sf::Vector2f(Constants::GRID_SIZE, 0.f);
    vertices[2].position = sf::Vector2f(Constants::GRID_SIZE, Constants::GRID_SIZE);
    vertices[3].position = sf::Vector2f(0.f, 0.f);
    vertices[4].position = sf::Vector2f(0.f, Constants::GRID_SIZE);
    vertices[5].position = sf::Vector2f(Constants::GRID_SIZE, Constants::GRID_SIZE);

    vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
    vertices[1].texCoords = sf::Vector2f(Constants::GRID_SIZE, 0.f);
    vertices[2].texCoords = sf::Vector2f(Constants::GRID_SIZE, Constants::GRID_SIZE);
    vertices[3].texCoords = sf::Vector2f(0.f, 0.f);
    vertices[4].texCoords = sf::Vector2f(0.f, Constants::GRID_SIZE);
    vertices[5].texCoords = sf::Vector2f(Constants::GRID_SIZE, Constants::GRID_SIZE);

    setDimmed(false);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = texture.get();
    target.draw(vertices, states);
}

sf::Vector2i Entity::getGridPosition() const {
    return {(int) (this->getPosition().x / Constants::GRID_SIZE), (int) (this->getPosition().y / Constants::GRID_SIZE)};
}

void Entity::setGridPosition(const sf::Vector2i &pos) {
    this->setGridPosition(pos.x, pos.y);
}

void Entity::setGridPosition(int x, int y) {
    this->setPosition(sf::Vector2f((float) (x * Constants::GRID_SIZE), (float) (y * Constants::GRID_SIZE)));
}