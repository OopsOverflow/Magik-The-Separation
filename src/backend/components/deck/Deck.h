//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_DECK_H
#define MAGIK_DECK_H

#include "../card/Card.h"
class Deck {
public : 
    virtual void add();
    virtual uint8_t getLenght() const;
};


#endif //MAGIK_DECK_H
