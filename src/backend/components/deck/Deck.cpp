//
// Created by houssem on 04/01/2022.
//

#include "Deck.h"
#include <stdexcept>

Deck::Deck() {

}

CardType Deck::getCardType(Card* card) {
    if(dynamic_cast<Creature*> (card)) return CardType::CREATURE;
    if(dynamic_cast<Enchantement*> (card)) return CardType::ENCHANTEMENT;
    if(dynamic_cast<Instant*> (card)) return CardType::INSTANT;
    if(dynamic_cast<Land*> (card)) return CardType::LAND;
    /* if(dynamic_cast<Sorcery*> (card)) */ return CardType::SORCERY;

    //std::runtime_error("no type was found");
}
