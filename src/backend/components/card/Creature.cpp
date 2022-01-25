//
// Created by houssem on 04/01/2022.
//

#include "Creature.h"


Creature::Creature(uint8_t id, const std::string &name, std::map<Color, int> cost, uint8_t power, uint8_t thougness) 
: Card(id, name, cost), stats({power, thougness}), summoningSickness(true) {

}

Creature::~Creature() {

}

std::pair<int, int> Creature::getBaseStats() const {
    return stats;
}

std::pair<int, int> Creature::getTotalStats() {
    std::pair<int, int> result = stats;
    for(auto modifier : modifiers) {
        stats.first += modifier.first;
        stats.second += modifier.second;
    }
    return result;
        
}

std::pair<int, int> Creature::getTmpStats() {
    std::pair<int, int> result = getTotalStats();
    for(auto modifier : tmpModifiers) {
        stats.first += modifier.first;
        stats.second += modifier.second;
    }
    return result;
}

void Creature::addTmpStat(std::pair<int,int> stat) {
    tmpModifiers.push_back(stat);
}

void Creature::addStaticAbility(StaticAbility ability) {
    staticAbilities.push_back(ability);
}

void Creature::block(Creature* attackingCard) {
    if(attackingCard->hasStaticAbility(StaticAbility::FIRST_STRIKE) || attackingCard->hasStaticAbility(StaticAbility::DOUBLE_STRIKE))
    {
        if(attackingCard->hasStaticAbility(StaticAbility::DEATHTOUCH) && attackingCard->getTmpStats().first > 0) {
            attackingCard->addTmpStat({-1, 0});
            this->addTmpStat({0, -this->getTmpStats().second});
        }else if(attackingCard->getTmpStats().first >= this->getTmpStats().second) {
            attackingCard->addTmpStat({-this->getTmpStats().second, 0});
            this->addTmpStat({0, -this->getTmpStats().second});
        } else {
            attackingCard->addTmpStat({-attackingCard->getTmpStats().first, 0});
            this->addTmpStat({0, -attackingCard->getTmpStats().first});
        }
    }
    if(!attackingCard->hasStaticAbility(StaticAbility::FIRST_STRIKE) && this->getTmpStats().second > 0) {
        if(attackingCard->hasStaticAbility(StaticAbility::DEATHTOUCH) && attackingCard->getTmpStats().first > 0) {
            attackingCard->addTmpStat({-1, -this->getTmpStats().first});
            this->addTmpStat({-this->getTmpStats().first, -this->getTmpStats().second});
        }else if(attackingCard->getTmpStats().first >= this->getTmpStats().second) {
            attackingCard->addTmpStat({-this->getTmpStats().second, -this->getTmpStats().first});
            this->addTmpStat({-this->getTmpStats().first, -this->getTmpStats().second});
        } else {
            attackingCard->addTmpStat({-attackingCard->getTmpStats().first, -this->getTmpStats().first});
            this->addTmpStat({-this->getTmpStats().first, -attackingCard->getTmpStats().first});
        }
    }

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

bool Creature::isSummoned() {
    return summoningSickness && !hasStaticAbility(StaticAbility::HASTE);
}

void Creature::newTurn() {
    summoningSickness = false;
    tmpModifiers.clear();
}