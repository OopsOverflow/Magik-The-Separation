//
// Created by houssem on 04/01/2022.
//

#include "Enchantement.h"

Enchantement::Enchantement(const std::string &name, std::unordered_map<Color, int> cost) : Card(name, cost) {

}

Enchantement::~Enchantement() {
    
}


void Enchantement::addStaticAbility(std::function<void()> ability) {
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