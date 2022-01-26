//
// Created by houssem on 04/01/2022.
//

#include "Creature.h"
#include <algorithm>
#include <utility>


Creature::Creature(uint16_t id, const std::string &name, std::map<Color, int> cost, uint16_t power, uint16_t thougness) 
: Card(id, name, std::move(cost)), summoningSickness(true), stats({power, thougness}) {

}

Creature::~Creature() = default;

std::pair<int, int> Creature::getBaseStats() const {
    return stats;
}

std::pair<int, int> Creature::getTotalStats() {
    std::pair<int, int> result = stats;
    for(auto modifier : modifiers) {
        result.first += modifier.first;
        result.second += modifier.second;
    }
    return result;
        
}

std::pair<int, int> Creature::getTmpStats() {
    std::pair<int, int> result = getTotalStats();
    for(auto modifier : tmpModifiers) {
        result.first += modifier.first;
        result.second += modifier.second;
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
        std::cout<<attackingCard->getName()<<" attacks "<<this->getName()<<std::endl;
        if(attackingCard->hasStaticAbility(StaticAbility::DEATHTOUCH) && attackingCard->getTmpStats().first > 0) {
            auto atk = attackingCard->getTmpStats();
            auto def = this->getTmpStats();
            attackingCard->addTmpStat({-1, 0});
            this->addTmpStat({0, -def.second});
        }else if(attackingCard->getTmpStats().first >= this->getTmpStats().second) {
            auto atk = attackingCard->getTmpStats();
            auto def = this->getTmpStats();
            attackingCard->addTmpStat({-def.second, 0});
            this->addTmpStat({0, -def.second});
        } else {
            auto atk = attackingCard->getTmpStats();
            auto def = this->getTmpStats();
            attackingCard->addTmpStat({-atk.first, 0});
            this->addTmpStat({0, -atk.first});
        }
    }
    if(!attackingCard->hasStaticAbility(StaticAbility::FIRST_STRIKE) && this->getTmpStats().second > 0) {
        std::cout<<"Duel between "<<attackingCard->getName()<<" and "<<this->getName()<<std::endl;
        
        if(attackingCard->hasStaticAbility(StaticAbility::DEATHTOUCH) && attackingCard->getTmpStats().first > 0) {
            auto atk = attackingCard->getTmpStats();
            auto def = this->getTmpStats();
            attackingCard->addTmpStat({-1, -def.first});
            this->addTmpStat({-def.first, -def.second});
        }else if(attackingCard->getTmpStats().first >= this->getTmpStats().second) {
            auto atk = attackingCard->getTmpStats();
            auto def = this->getTmpStats();
            attackingCard->addTmpStat({-def.second, -def.first});
            this->addTmpStat({-def.first, -def.second});
        } else {
            auto atk = attackingCard->getTmpStats();
            auto def = this->getTmpStats();
            attackingCard->addTmpStat({-atk.first, -def.first});
            this->addTmpStat({-def.first, -atk.first});
        }
        

    }else if (this->getTmpStats().second > 0){
        std::cout<<attackingCard->getName()<<" blocks "<<this->getName()<<std::endl;
        attackingCard->addTmpStat({0, -this->getTmpStats().first});
        this->addTmpStat({-this->getTmpStats().first, 0});

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

std::string Creature::displayStaticAbilitites() {
    std::string displayTable[12] = {"FLY", "REACH", "VIGILANCE", "DEATHTOUCH", "DEFENDER", "FIRST_STRIKE", "DOUBLE_STRIKE", "HASTE", "CANT_BE_BLOCKED", "LIFELINK", "INTIMIDATE", "TRAMPLE"};
    std::string result = "(";
    for(size_t i = 0; i<staticAbilities.size(); i += 1) {
        result += displayTable[(int)staticAbilities.at(i)];
        if(i != staticAbilities.size()-1)result += ", ";
    }
    result += ")";
    return result;
}