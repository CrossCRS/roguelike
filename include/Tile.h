#pragma once

class Tile {
public:
    explicit Tile(unsigned int textureId, bool isImpenetrable = false) : textureId(textureId),
                                                                         isImpenetrable_(isImpenetrable) {}

    inline unsigned int getTextureId() const { return textureId; }

    inline bool isImpenetrable() const { return isImpenetrable_; }

    inline bool isVisible() const { return true; } // Może kiedyś
private:
    unsigned int textureId;
    bool isImpenetrable_;
};