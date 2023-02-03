#pragma once

#include "Attribute.h"
#include "Entities/Entity.h"
#include "GUI/GUIHealthBar.h"
#include "System/Inventory.h"

#include <magic_enum.hpp>

#define INVENTORY_SLOTS 24

class Character : public Entity {
public:
    Character(int id, std::shared_ptr<sf::Texture> texture, World &world) :
        Entity(id, std::move(texture), world),
        name("Unknown"),
        inventory(this, INVENTORY_SLOTS),
        guiHealthBar(std::make_unique<GUIHealthBar>(*this, true)),
        speed(1.f),
        bcanInteractWithObjects(true) {}

    virtual bool isPlayer() const;

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

    Inventory &getInventory();

    virtual void onDamageTaken(Entity *source, int damage);
    virtual void onDeath();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update() override;

private:
    std::string name;
    
    Attribute attributes[magic_enum::enum_count<AttributeIndex>()];
    Inventory inventory;

    std::unique_ptr<GUIHealthBar> guiHealthBar;

    float speed;
    bool bcanInteractWithObjects;
};