//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_GRAVEYARD_H
#define MAGIK_GRAVEYARD_H

#include "Deck.h"
#include <vector>
#include <memory>

class Graveyard : public Deck {
public : 
    Graveyard(std::vector<std::unique_ptr<Card> >cards);
    Graveyard();
    ~Graveyard();

    std::unique_ptr<Card> getCard(uint8_t cardNum);
    uint8_t getLenght() const;
private : 
    std::vector<std::unique_ptr<Card> > cards;
};


#endif //MAGIK_GRAVEYARD_H
