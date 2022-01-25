//
// Created by houssem on 04/01/2022.
//

#include "Ability.h"

Ability::Ability(uint16_t id, std::string name,
                 std::function<void(Player*, Card*, std::vector<std::pair<Player*, Card*> >) > fct) :
                 Card(id, name, {}), fct(fct) {

}

