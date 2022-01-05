//
// Created by houssem on 04/01/2022.
//

#include "Ability.h"

Ability::Ability(std::string name, std::string reminderText, std::string flavorText) : 
    name(name), reminderText(reminderText), flavorText(flavorText) {

}

std::string Ability::getName() {
    return name;
}

std::string Ability::getReminderText() {
    return reminderText;
}

std::string Ability::getFlavorText() {
    return flavorText;
}