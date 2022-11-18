#pragma once

#include "BaseTile.h"

class DoorTile : public BaseTile {
public:
    explicit DoorTile(unsigned int textureIdClosed, unsigned int textureIdOpen, bool isClosed = true) :
        BaseTile(textureIdClosed),
        textureIdClosed(textureIdClosed),
        textureIdOpen(textureIdOpen),
        isClosed(isClosed) {}

    unsigned int getTextureId() const override {
        return isClosed ? textureIdClosed : textureIdOpen;
    }

    void interact(Character &/*character*/) override {
        if (isClosed) isClosed = false;
    }

    bool isImpenetrable() override {
        return isClosed;
    }
private:
    unsigned int textureIdClosed;
    unsigned int textureIdOpen;

    bool isClosed;
};