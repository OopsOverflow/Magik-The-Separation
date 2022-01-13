//
// Created by pierre on 05/01/2022.
//

#ifndef MAGIK_TRIGGERED_ABILITY_H
#define MAGIK_TRIGGERED_ABILITY_H
#include "Ability.h"


enum class Event{ATTACK, BLOCKING,
OPPONENT_CARD_DIES, CREATURE_DIES, OWNER_CARD_DIES,
BEGINNING_OF_UPKEEP_STEP, END_OF_UPKEEP_STEP,};

class TriggeredAbility : public Ability {
public :

private :
};


#endif //MAGIK_TRIGGERED_ABILITY_H
