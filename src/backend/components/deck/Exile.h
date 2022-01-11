//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_EXILE_H
#define MAGIK_EXILE_H

#include "Deck.h"
#include <vector>
#include <memory>

class Exile : public Deck {
public : 
    Exile(std::vector<std::unique_ptr<Card> >cards);
    Exile();
    ~Exile();

    std::unique_ptr<Card> getCard(uint8_t cardNum);
    uint8_t getLenght() const;
private : 
    std::vector<std::unique_ptr<Card> > cards;
};


#endif //MAGIK_EXILE_H
