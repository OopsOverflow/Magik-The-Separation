//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_GRAVEYARD_H
#define MAGIK_GRAVEYARD_H

#include <vector>
#include "Deck.h"

class Graveyard : public Deck {
public : 
    Graveyard();
    ~Graveyard();

    uint16_t getLength() const;

    void add(std::unique_ptr<Card> card);
    std::unique_ptr<Card> popCard(uint16_t cardId);
    Card* getCard(uint16_t cardId);
    

private : 
    std::vector<std::unique_ptr<Card> > cards;

};


#endif //MAGIK_GRAVEYARD_H
