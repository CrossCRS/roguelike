#pragma once

class Tile {
public:
    explicit Tile(unsigned int textureId, bool isImpenetrable = false, bool isInteractive = false) : textureId(textureId),
                                                                                                     isImpenetrable_(isImpenetrable),
                                                                                                     isInteractive_(isInteractive) {}

    unsigned int getTextureId() const { return textureId; }

    bool isImpenetrable() const { return isImpenetrable_; }
    bool isInteractive() const { return isInteractive_; }
    bool isVisible() const { return true; } // Może kiedyś
private:
    unsigned int textureId;
    bool isImpenetrable_;
    bool isInteractive_;
};