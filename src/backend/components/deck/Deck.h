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

    virtual uint8_t getLength() const=0;
    static CardType getCardType(Card* card);

    virtual ~Deck() = default;
};


#endif //MAGIK_DECK_H
