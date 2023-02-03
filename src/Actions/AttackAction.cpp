#include "Actions/AttackAction.h"

#include "Item.h"
#include "spdlog/spdlog.h"
#include "effolkronium/random.hpp"

using Random = effolkronium::random_static;

void AttackAction::execute() {
    const auto attackerWeapon = character->getInventory().getItemInSlot(ItemSlot::RIGHT_HAND);

    const int attackerStr = character->getCurrentAttribute(AttributeIndex::STRENGTH);
    const int attackerDex = character->getCurrentAttribute(AttributeIndex::DEXTERITY);
    const int attackerDmg = (attackerWeapon == nullptr) ? 0 : attackerWeapon->getProperty(ItemProperty::DAMAGE);
    const int defenderDex = other->getCurrentAttribute(AttributeIndex::DEXTERITY);

    const float hitChance = attackerDex / (2.f * defenderDex) * Random::get(0.9f, 1.15f);
    const int damage = static_cast<int>(attackerStr + attackerDmg + (attackerDmg * (attackerStr * 0.1f)));

    spdlog::debug("ATTACK: HIT_CHANCE={0:.4f} DMG={1}", hitChance, damage);
}