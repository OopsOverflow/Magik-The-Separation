//
// Created by pierre on 05/01/2022.
//

#ifndef MAGIK_TRIGGERED_ABILITY_H
#define MAGIK_TRIGGERED_ABILITY_H
#include "Ability.h"



enum class Event{ATTACK, BLOCKING, SPAWN,
CREATURE_DIES,
BEGINNING_OF_UPKEEP_STEP, END_OF_UPKEEP_STEP};

class TriggeredAbility : public Ability {
public :
    bool isTriggered(Event event, Card* cardPlayed, Card* targetCard = nullptr);
private :
};


#endif //MAGIK_TRIGGERED_ABILITY_H
