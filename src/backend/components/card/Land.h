//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_LAND_H
#define MAGIK_LAND_H

#include "Card.h"

class Land : public Card {
public : 
    Land(uint8_t id, const std::string &name);
    ~Land();

    Land(Land const&) = delete;
    Land& operator=(Land const&) = delete;
};


#endif //MAGIK_LAND_H
