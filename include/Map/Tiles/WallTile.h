#pragma once

#include "BaseTile.h"

class WallTile : public BaseTile {
public:
    explicit WallTile(unsigned int textureId) : BaseTile(textureId) {}

    bool isImpenetrable() override { return true; }
};