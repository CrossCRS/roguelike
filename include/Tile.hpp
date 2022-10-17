#pragma once

class Tile {
    public:
        Tile(unsigned int textureId, bool isImpenetrable = false) : m_textureId(textureId), m_isImpenetrable(isImpenetrable) { }
        
        unsigned int getTextureId() const { return m_textureId; }
        bool isImpenetrable() const { return m_isImpenetrable; }
        bool isVisible() const { return true; } // Może kiedyś
    private:
        unsigned int m_textureId;
        bool m_isImpenetrable;
};