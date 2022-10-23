#pragma once

class Tile {
    public:
        explicit Tile(unsigned int textureId, bool isImpenetrable = false) : m_textureId(textureId), m_isImpenetrable(isImpenetrable) { }
        
        inline unsigned int getTextureId() const { return m_textureId; }
        inline bool isImpenetrable() const { return m_isImpenetrable; }
        inline bool isVisible() const { return true; } // Może kiedyś
    private:
        unsigned int m_textureId;
        bool m_isImpenetrable;
};