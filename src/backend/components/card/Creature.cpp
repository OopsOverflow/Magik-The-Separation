//
// Created by houssem on 04/01/2022.
//

#include "Creature.h"


Creature::Creature(const std::string &name, std::unordered_map<Color, int> cost, uint8_t power, uint8_t thougness) 
: Card(name, cost), power(power), thougness(thougness) {

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
    tempThougness -= attacker->getPower();
    attacker->takeDamage(power);
}

void Creature::takeDamage(uint8_t damages) {
    tempThougness -= damages;
}

int8_t Creature::getTempThougness() const {
    return tempThougness;
}

void Creature::addStaticAbility(std::function<void()> ability) {
    staticAbilities.push_back(ability);
}

void Creature::addActivatedAbility(std::function<void()> ability) {
    activatedAbilities.push_back(ability);
}

void Creature::addTriggeredAbility(std::function<void(Event)> ability) {
    triggeredAbilities.push_back(ability);
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