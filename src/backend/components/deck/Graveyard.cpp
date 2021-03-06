//
// Created by houssem on 04/01/2022.
//

#include "Graveyard.h"


Graveyard::Graveyard() {
}

Graveyard::~Graveyard() {

}

std::unique_ptr<Card> Graveyard::popCard(uint16_t cardNum) {
    std::unique_ptr<Card> ptr = std::move(cards.at((int)cardNum));
    cards.erase(cards.begin() + cardNum);
    return ptr;  
}

Card* Graveyard::getCard(uint16_t cardNum) {
    return cards.at((int)cardNum).get();
}

uint16_t Graveyard::getLength() const {
    return (uint16_t)cards.size();
}

void Graveyard::add(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}