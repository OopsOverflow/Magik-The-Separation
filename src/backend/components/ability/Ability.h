//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_ABILITY_H
#define MAGIK_ABILITY_H
#include "string"
#include "../card/Card.h"
class Ability : public Card {
public :
    Ability(uint8_t id, std::string name, std::map<Color, int> cost, std::string reminderText = "", std::string flavorText = "");
    std::string getReminderText() const;
    std::string getFlavorText() const;

private :
    std::string reminderText;
    std::string flavorText;
};


#endif //MAGIK_ABILITY_H
