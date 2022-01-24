//
// Created by houssem on 04/01/2022.
//

#include "Creature.h"


Creature::Creature(uint8_t id, const std::string &name, std::map<Color, int> cost, uint8_t power, uint8_t thougness) 
: Card(id, name, cost), power(power), thougness(thougness) {

}

Creature::~Creature() {

}

uint8_t Creature::getPower() const {
    return power;
}

uint8_t Creature::getThougness() const {
    return thougness;
}

void Creature::block(Creature* attacker) { //TODO add more complex interractions
    tempDamages -= attacker->getPower();
    attacker->takeDamage(power);
}

void Creature::takeDamage(uint8_t damages) {
    tempDamages -= damages;
}

int8_t Creature::getTempDamages() const {
    return tempDamages;
}

void Creature::addStaticAbility(StaticAbility ability) {
    staticAbilities.push_back(ability);
}

// void Creature::addActivatedAbility(std::function<void()> ability) {
//     activatedAbilities.push_back(ability);
// }

// void Creature::addTriggeredAbility(std::function<void(Event)> ability) {
//     triggeredAbilities.push_back(ability);
// }

std::vector<TriggeredAbility > Creature::getTriggerAbilities() const {
    return triggeredAbilities;
}

std::vector<ActivatedAbility > Creature::getActivatedAbilities() const {
    return activatedAbilities;
}

std::vector<Enchantement*> Creature::getAttachedCards() {
    std::vector<Enchantement*> result;
    for(auto const& enchant: attachedEnchantments)
        result.push_back(enchant.get());

    return result;
}

void Creature::attachCard(std::unique_ptr<Enchantement> card) {
    attachedEnchantments.push_back(std::move(card));
}

bool Creature::hasStaticAbility(StaticAbility ability) {
    auto it = std::find(staticAbilities.begin(), staticAbilities.end(), ability);
    return it != staticAbilities.end();
}