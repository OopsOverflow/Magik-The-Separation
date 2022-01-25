//
// Created by houssem on 04/01/2022.
//

#include "Enchantement.h"

#include <utility>

Enchantement::Enchantement(uint16_t id, const std::string &name, std::map<Color, int> cost) : Card(id, name, std::move(cost)) {

}

Enchantement::~Enchantement() = default;


void Enchantement::addStaticAbility(StaticAbility ability) {
    staticAbilities.push_back(ability);
}

void Enchantement::addActivatedAbility(const std::function<void()>& ability) {
    activatedAbilities.push_back(ability);
}

void Enchantement::addTriggeredAbility(const std::function<void(Event)>& ability) {
    triggeredAbilities.push_back(ability);
}

std::vector<std::function<void(Event)> > Enchantement::getTriggerAbilities() const {
    return triggeredAbilities;
}