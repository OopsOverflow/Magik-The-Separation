//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_SORCERY_H
#define MAGIK_SORCERY_H

#include "Card.h"

class Sorcery : public Card {
public : 
    Sorcery(uint16_t id, const std::string &name, std::map<Color, int> cost);
    ~Sorcery() override;

    Sorcery(Sorcery const&) = delete;
    Sorcery& operator=(Sorcery const&) = delete;
};


#endif //MAGIK_SORCERY_H
