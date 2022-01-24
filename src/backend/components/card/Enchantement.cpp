//
// Created by houssem on 04/01/2022.
//

#include "Enchantement.h"

Enchantement::Enchantement(uint8_t id, const std::string &name, std::map<Color, int> cost) : Card(id, name, cost) {

}

Enchantement::~Enchantement() {
    
}


void Enchantement::addStaticAbility(StaticAbility ability) {
    staticAbilities.push_back(ability);
}

void Enchantement::addActivatedAbility(std::function<void()> ability) {
    activatedAbilities.push_back(ability);
}

void Enchantement::addTriggeredAbility(std::function<void(Event)> ability) {
    triggeredAbilities.push_back(ability);
}

std::vector<std::function<void(Event)> > Enchantement::getTriggerAbilities() const {
    return triggeredAbilities;
}