//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_DECK_H
#define MAGIK_DECK_H

#include "../card/Card.h"
#include <vector>
#include <memory>
class Deck {
public : 
    virtual void add(std::unique_ptr<Card> card);
    virtual uint8_t getLenght() const;
    virtual std::unique_ptr<Card> getCard(uint8_t cardNum);
};


#endif //MAGIK_DECK_H
