#pragma once

#include "Attribute.h"
#include "Entities/Entity.h"

#include <magic_enum.hpp>

class Character : public Entity {
public:
    Character(int id, std::shared_ptr<sf::Texture> texture, World &world) :
        Entity(id, std::move(texture), world),
        name("Unknown"),
        speed(1.f),
        bcanInteractWithObjects(true) {}

    int getCurrentAttribute(AttributeIndex index) const;
    int getBaseAttribute(AttributeIndex index) const;

    void setCurrentAttribute(AttributeIndex index, int value);
    void setBaseAttribute(AttributeIndex index, int value);

    float getSpeed() const;
    void setSpeed(float newSpeed);

    bool canInteractWithObjects() const;
    void setCanInteractWithObjects(bool value);

    const std::string &getName() const;
    void setName(const std::string& _name);

private:
    std::string name;
    
    Attribute attributes[magic_enum::enum_count<AttributeIndex>()];

    float speed;
    bool bcanInteractWithObjects;
};