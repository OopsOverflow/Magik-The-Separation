//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_DECK_H
#define MAGIK_DECK_H

#include "../card/Card.h"
#include <memory>

class Deck {
public :
    Deck();

    virtual void add(std::unique_ptr<Card> card);
    virtual uint8_t getLenght() const;
    virtual Card* getCard(uint8_t cardNum);
    virtual std::unique_ptr<Card> popCard(uint8_t cardNum);

    virtual ~Deck() = default;
};


#endif //MAGIK_DECK_H
