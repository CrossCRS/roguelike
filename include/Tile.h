#pragma once

class Tile {
public:
    explicit Tile(unsigned int textureId, bool isImpenetrable = false) : textureId(textureId),
                                                                         isImpenetrable_(isImpenetrable) {}

    unsigned int getTextureId() const { return textureId; }

    bool isImpenetrable() const { return isImpenetrable_; }

    bool isVisible() const { return true; } // Może kiedyś
private:
    unsigned int textureId;
    bool isImpenetrable_;
};