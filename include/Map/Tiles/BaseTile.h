#pragma once

class Character;

class BaseTile {
public:
    explicit BaseTile(unsigned int textureId) : textureId(textureId) {}
    virtual ~BaseTile() = default;

    virtual unsigned int getTextureId() const { return textureId; }

    virtual void interact(Character */*character*/) {}

    virtual bool isImpenetrable() = 0;
private:
    unsigned int textureId;
};