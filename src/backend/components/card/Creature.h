//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_CREATURE_H
#define MAGIK_CREATURE_H

#include "Card.h"
#include "../ability/ActivatedAbility.h"
#include "../ability/TriggeredAbility.h"
#include "Enchantement.h"

#include <functional>
#include <memory>
#include <vector>
#include <iostream>


template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T, S>& v)
{
    os << "(";
    os << v.first << ", " 
       << v.second << ")";
    return os;
}

class Creature : public Card {
public :
    Creature(uint16_t id, const std::string &name, std::map<Color, int> cost, uint16_t power, uint16_t thougness);
    ~Creature();

    Creature(Creature const&) = delete;
    Creature& operator=(Creature const&) = delete;

    std::string displayStaticAbilitites();

    std::pair<int, int> getBaseStats() const; //Creature flat stats
    std::pair<int, int> getTotalStats(); //Creature permanent buffed stats
    std::pair<int, int> getTmpStats(); //Creature temp stats (stats during the turn)

    void addTmpStat(std::pair<int,int> stat);
    void block(Creature* attackingCard);

    void addStaticAbility(StaticAbility ability);
    // void addActivatedAbility(std::function<void()> ability);
    // void addTriggeredAbility(std::function<void(Event)> ability);

    std::vector<TriggeredAbility > getTriggerAbilities() const;
    std::vector<ActivatedAbility > getActivatedAbilities() const;

    std::vector<Enchantement*> getAttachedCards();
    void attachCard(std::unique_ptr<Enchantement> card);

    bool hasStaticAbility(StaticAbility ability);

    bool isSummoned();
    void newTurn();

private :

    bool summoningSickness;
    std::pair<int, int> stats; 
    std::vector<std::pair<int, int> >modifiers; 
    std::vector<std::pair<int,int> > tmpModifiers;

    std::vector<StaticAbility> staticAbilities;
    std::vector<ActivatedAbility > activatedAbilities;
    std::vector<TriggeredAbility > triggeredAbilities;

    std::vector<std::unique_ptr<Enchantement> > attachedEnchantments;
};


#endif //MAGIK_CREATURE_H
