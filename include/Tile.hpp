#pragma once

class Tile {
    public:
        Tile(unsigned int textureId, bool isImpenetrable = false) : m_textureId(textureId), m_isImpenetrable(isImpenetrable) { }
        
        unsigned int getTextureId() { return m_textureId; }
        bool isImpenetrable() { return m_isImpenetrable; }
        bool isVisible() { return true; } // Może kiedyś
    private:
        unsigned int m_textureId;
        bool m_isImpenetrable;
};