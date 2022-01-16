//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_SORCERY_H
#define MAGIK_SORCERY_H

#include "Card.h"

class Sorcery : public Card {
public : 
    Sorcery(uint8_t id, const std::string &name, std::unordered_map<Color, int> cost);
    ~Sorcery();

    Sorcery(Sorcery const&) = delete;
    Sorcery& operator=(Sorcery const&) = delete;
};


#endif //MAGIK_SORCERY_H
