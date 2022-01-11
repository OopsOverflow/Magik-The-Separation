//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_BATTLEFIELD_H
#define MAGIK_BATTLEFIELD_H

#include "Deck.h"


class Battlefield : public Deck{
public : 
    Battlefield(std::vector<std::unique_ptr<Card> >cards);
    Battlefield();
    ~Battlefield();

    std::unique_ptr<Card> getCard(uint8_t cardNum);
    uint8_t getLenght() const;

    void unTap(uint8_t cardNum);  

    void add(std::unique_ptr<Card> card);
private : 
    std::vector<std::unique_ptr<Card> > cards;
};


#endif //MAGIK_BATTLEFIELD_H
