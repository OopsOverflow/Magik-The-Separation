//
// Created by houssem on 04/01/2022.
//

#include "Ability.h"

Ability::Ability(uint16_t id, std::string name, std::map<Color, int> cost, std::string reminderText, std::string flavorText) : Card(id, name, cost), 
     reminderText(reminderText), flavorText(flavorText) {

}

std::string Ability::getReminderText() const {
    return reminderText;
}

std::string Ability::getFlavorText() const {
    return flavorText;
}