//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_ABILITY_H
#define MAGIK_ABILITY_H
#include "string"
#include "../card/Card.h"
#include <functional>

class Player;
class Ability : public Card {
public :
    Ability(uint16_t id, std::string name, std::function<void(Player*, Card*, std::vector<std::pair<Player*, Card*> >) > fct);

private :
    //Caster, Casting Card, Targeted Cards + Owners
    std::function<void(Player*, Card*, std::vector<std::pair<Player*, Card*> >) > fct;
};


#endif //MAGIK_ABILITY_H
