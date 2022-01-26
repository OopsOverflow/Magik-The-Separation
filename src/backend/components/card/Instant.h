//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_INSTANT_H
#define MAGIK_INSTANT_H

#include "Card.h"

class Instant : public Card {
public : 
    Instant(uint16_t id, const std::string &name, std::map<Color, int> cost);
    ~Instant() override;

    Instant(Instant const&) = delete;
    Instant& operator=(Instant const&) = delete;

};


#endif //MAGIK_INSTANT_H
