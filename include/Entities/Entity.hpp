#pragma once
#include "Constants.hpp"
#include "System/ResourceManager.hpp"

#include <SFML/Graphics.hpp>

// TODO: Pass texture shared_ptr instead of ResourceManager?
class Entity : public sf::Drawable, public sf::Transformable {
    public:
        Entity(int id, const std::string& textureName, ResourceManager& resourceManager);

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

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::Vector2i getGridPosition() const;
        void setGridPosition(const sf::Vector2i& pos);
        void setGridPosition(int x, int y);

    protected:
        int id;
        bool dimmed;

        ResourceManager& m_resourceManager;
        sf::VertexArray m_vertices;
        std::shared_ptr<sf::Texture> m_texture;
};