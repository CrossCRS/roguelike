#pragma once

#include "Entities/Entity.h"

class BaseTile {
public:
    explicit BaseTile(unsigned int textureId) : textureId(textureId) {}
    virtual ~BaseTile() = default;

    virtual unsigned int getTextureId() const { return textureId; }

    virtual void interact(Entity &/*entity*/) {}

    virtual bool isImpenetrable() = 0;
private:
    unsigned int textureId;
};