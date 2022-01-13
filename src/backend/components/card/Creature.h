//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_CREATURE_H
#define MAGIK_CREATURE_H

#include "Card.h"
#include "../ability/StaticAbility.h"
#include "../ability/ActivatedAbility.h"
#include "../ability/TriggeredAbility.h"

#include <functional>

enum class SUBTYPE{ANGEL};

class Creature : public Card {
public :
    Creature(const std::string &name, std::unordered_map<std::string, int> cost, uint8_t power, uint8_t thougness);
    ~Creature();

    uint8_t getPower() const;
    uint8_t getThougness() const;
    

    void block(Creature* attacker);
    void takeDamage(uint8_t damages);

    int8_t getTempThougness() const;

    void addStaticAbility(std::vector<std::function<void()> > ability);
    void addActivatedAbility(std::vector<std::function<void()> > ability);
    void addTriggeredAbility(std::vector<std::function<void(Event)> > ability);

    std::vector<std::function<void(Event)> > getTriggerAbilities() const;

private :
    uint8_t power;
    uint8_t thougness;

    int8_t tempThougness;

    std::vector<std::function<void()> > staticAbilities;
    std::vector<std::function<void()> > activatedAbilities;
    std::vector<std::function<void(Event)> > triggeredAbilities;
};


#endif //MAGIK_CREATURE_H
