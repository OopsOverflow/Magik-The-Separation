//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_BATTLEFIELD_H
#define MAGIK_BATTLEFIELD_H

#include <vector>
#include "Deck.h"


class Battlefield : public Deck{
public : 
    Battlefield();
    ~Battlefield();

    std::unique_ptr<Card> popCard(uint8_t cardNum);
    Card* getCard(uint8_t cardNum) final;
    uint8_t getLenght() const final;
    int8_t getCardIndex(Card* card);

    void unTap(uint8_t cardNum);  

    void add(std::unique_ptr<Card> card) final;

private : 
    std::vector<std::unique_ptr<Card> > cards;
};


#endif //MAGIK_BATTLEFIELD_H
