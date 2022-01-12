//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_EXILE_H
#define MAGIK_EXILE_H

#include <vector>
#include "Deck.h"

class Exile : public Deck {
public : 
    Exile();
    virtual ~Exile();

    std::unique_ptr<Card> popCard(uint8_t cardNum);
    Card* getCard(uint8_t cardNum) final;
    uint8_t getLenght() const final;

private : 
    std::vector<std::unique_ptr<Card> > cards;
};


#endif //MAGIK_EXILE_H
