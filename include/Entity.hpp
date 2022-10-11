#pragma once

#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable {
    public:
        Entity(int id, const std::string& textureName, ResourceManager& resourceManager) : m_resourceManager(resourceManager), id(id) { 
            m_texture = m_resourceManager.getTexture(textureName);
            m_vertices.setPrimitiveType(sf::TriangleStrip);
            m_vertices.resize(4);

            dimmed = false;

            // All sprites are 32x32
            m_vertices[0].position = sf::Vector2f(32.f, 0.f);
            m_vertices[1].position = sf::Vector2f(0.f, 0.f);
            m_vertices[2].position = sf::Vector2f(32.f, 32.f);
            m_vertices[3].position = sf::Vector2f(0.f, 32.f);

            m_vertices[0].texCoords = sf::Vector2f(32.f, 0.f);
            m_vertices[1].texCoords = sf::Vector2f(0.f, 0.f);
            m_vertices[2].texCoords = sf::Vector2f(32.f, 32.f);
            m_vertices[3].texCoords = sf::Vector2f(0.f, 32.f);

            // Might be useful for FOV? Eventually...
            if (dimmed) {
                m_vertices[0].color = sf::Color(64, 64, 64);
                m_vertices[1].color = sf::Color(64, 64, 64);
                m_vertices[2].color = sf::Color(64, 64, 64);
                m_vertices[3].color = sf::Color(64, 64, 64);
            }
        }

        inline int getId() { return id; }
        inline void setId(int _id) { id = _id; }

        inline bool isDimmed() { return dimmed; }
        inline void setDimmed(bool _dimmed) { dimmed = _dimmed; }

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
            states.transform *= getTransform();
            states.texture = m_texture.get();
            target.draw(m_vertices, states);
        }

    protected:
        int id;
        bool dimmed;

        ResourceManager& m_resourceManager;
        sf::VertexArray m_vertices;
        std::shared_ptr<sf::Texture> m_texture;
};