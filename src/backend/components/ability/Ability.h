//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_ABILITY_H
#define MAGIK_ABILITY_H
#include "string"

class Ability {
public :
    Ability(std::string name, std::string reminderText = "", std::string flavorText = "");
    std::string getName() const;
    std::string getReminderText() const;
    std::string getFlavorText() const;

private :
    std::string name;
    std::string reminderText;
    std::string flavorText;
};


#endif //MAGIK_ABILITY_H
