#pragma once

#include "Attribute.h"
#include "Entities/Entity.h"

class Character : public Entity {
public:
    Character(int id, std::shared_ptr<sf::Texture> texture, World &world) :
        Entity(id, std::move(texture), world),
        name("Unknown"),
        speed(1.f) {}

    int getCurrentAttribute(Attribute::Index index) const;
    int getBaseAttribute(Attribute::Index index) const;

    void setCurrentAttribute(Attribute::Index index, int value);
    void setBaseAttribute(Attribute::Index index, int value);

    float getSpeed() const;
    void setSpeed(float newSpeed);

    const std::string &getName() const;
    void setName(const std::string& _name);

private:
    std::string name;
    
    Attribute attributes[Attribute::LAST];

    float speed;
};