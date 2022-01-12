//
// Created by houssem on 04/01/2022.
//

#include "Exile.h"

Exile::Exile(){
}

Exile::~Exile() {
}

std::unique_ptr<Card> Exile::popCard(uint8_t cardNum) {
    std::unique_ptr<Card> ptr = std::move(cards.at((int)cardNum));
    cards.erase(cards.begin() + cardNum);
    return ptr;  
}

Card* Exile::getCard(uint8_t cardNum) {
    return cards.at((int)cardNum).get();
}

uint8_t Exile::getLenght() const {
    return (uint8_t)cards.size();
}