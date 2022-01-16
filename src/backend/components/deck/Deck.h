//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_DECK_H
#define MAGIK_DECK_H

#include "../card/Card.h"
#include "../card/Creature.h"
#include "../card/Enchantement.h"
#include "../card/Instant.h"
#include "../card/Land.h"
#include "../card/Sorcery.h"

#include <memory>
#include <iostream>

class Deck {
public :
    Deck();

    virtual void add(std::unique_ptr<Card> card);
    virtual uint8_t getLength() const;

    static CardType getCardType(Card* card);
    virtual std::unique_ptr<Card> popCard(uint8_t cardId);

    virtual ~Deck() = default;
};


#endif //MAGIK_DECK_H
