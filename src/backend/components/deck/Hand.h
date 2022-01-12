//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_HAND_H
#define MAGIK_HAND_H

#include <vector>
#include "Deck.h"

class Hand : public Deck {
public : 
    Hand();
    ~Hand();

    std::unique_ptr<Card> popCard(uint8_t cardNum);
    Card* getCard(uint8_t cardNum) final;
    uint8_t getLenght() const final;

    void add(std::unique_ptr<Card> card) final;

private : 
    std::vector<std::unique_ptr<Card> > cards;
};


#endif //MAGIK_HAND_H
