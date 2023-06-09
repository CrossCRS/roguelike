#pragma once

#include "BaseTile.h"

class FloorTile : public BaseTile {
public:
    explicit FloorTile(unsigned int textureId) : BaseTile(textureId) {}

    bool isImpenetrable() override { return false; }
};