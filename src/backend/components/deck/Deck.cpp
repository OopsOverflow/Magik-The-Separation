//
// Created by houssem on 04/01/2022.
//

#include "Deck.h"

Deck::Deck() {

}

void Deck::add(std::unique_ptr<Card> card) {

}

Card *Deck::getCard(uint8_t cardNum) {
    return nullptr;
}

std::unique_ptr<Card> Deck::popCard(uint8_t cardNum) {
    return std::unique_ptr<Card>();
}

uint8_t Deck::getLenght() const {
    return 0;
}
