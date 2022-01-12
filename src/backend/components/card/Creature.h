//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_CREATURE_H
#define MAGIK_CREATURE_H

#include "Card.h"

enum class SUBTYPE{ANGEL};

class Creature : Card {
public :
    Creature(const std::string &name, std::unordered_map<std::string, int> cost);
    ~Creature();

    uint8_t getPower() const;
    uint8_t getThougness() const;
    

    void block(Creature* attacker);
    void takeDamage(uint8_t damages);

    int8_t getTempThougness() const;

private :
    uint8_t power;
    uint8_t thougness;

    int8_t tempThougness;

};


#endif //MAGIK_CREATURE_H
