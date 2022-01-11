//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_HAND_H
#define MAGIK_HAND_H

#include "Deck.h"
#include <vector>
#include <memory>

class Hand : public Deck {
public : 
    Hand(std::vector<std::unique_ptr<Card> >cards);
    Hand();
    ~Hand();

    std::unique_ptr<Card> getCard(uint8_t cardNum);
    uint8_t getLenght() const;

    void add(std::unique_ptr<Card> card);
private : 
    std::vector<std::unique_ptr<Card> > cards;
};


#endif //MAGIK_HAND_H
