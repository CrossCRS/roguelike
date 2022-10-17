#pragma once
#include "System/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

// TODO: Pass texture shared_ptr instead of ResourceManager?
class Entity : public sf::Drawable, public sf::Transformable {
    public:
        Entity(int id, const std::string& textureName, ResourceManager& resourceManager) : id(id), m_resourceManager(resourceManager) { 
            m_texture = m_resourceManager.getTexture(textureName);
            m_vertices.setPrimitiveType(sf::Triangles);
            m_vertices.resize(6);

            // All sprites are 32x32
            m_vertices[0].position = sf::Vector2f(0.f, 0.f);
            m_vertices[1].position = sf::Vector2f(32.f, 0.f);
            m_vertices[2].position = sf::Vector2f(32.f, 32.f);
            m_vertices[3].position = sf::Vector2f(0.f, 0.f);
            m_vertices[4].position = sf::Vector2f(0.f, 32.f);
            m_vertices[5].position = sf::Vector2f(32.f, 32.f);

            m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
            m_vertices[1].texCoords = sf::Vector2f(32.f, 0.f);
            m_vertices[2].texCoords = sf::Vector2f(32.f, 32.f);
            m_vertices[3].texCoords = sf::Vector2f(0.f, 0.f);
            m_vertices[4].texCoords = sf::Vector2f(0.f, 32.f);
            m_vertices[5].texCoords = sf::Vector2f(32.f, 32.f);

            setDimmed(false);
        }

        inline int getId() const { return id; }
        inline void setId(int _id) { id = _id; }

        inline bool isDimmed() const { return dimmed; }
        inline void setDimmed(bool _dimmed) { 
            dimmed = _dimmed;

            // Might be useful for FOV? Eventually...
            if (dimmed) {
                m_vertices[0].color = sf::Color(64, 64, 64);
                m_vertices[1].color = sf::Color(64, 64, 64);
                m_vertices[2].color = sf::Color(64, 64, 64);
                m_vertices[3].color = sf::Color(64, 64, 64);
            }
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
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