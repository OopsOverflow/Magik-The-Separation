//
// Created by houssem on 04/01/2022.
//

#include "Ability.h"

Ability::Ability(uint8_t id, std::string name, std::unordered_map<Color, int> cost, std::string reminderText, std::string flavorText) : Card(id, name, cost), 
     reminderText(reminderText), flavorText(flavorText) {

}

std::string Ability::getReminderText() const {
    return reminderText;
}

std::string Ability::getFlavorText() const {
    return flavorText;
}