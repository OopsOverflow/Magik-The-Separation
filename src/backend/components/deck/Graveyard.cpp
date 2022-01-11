//
// Created by houssem on 04/01/2022.
//

#include "Graveyard.h"


Graveyard::Graveyard(std::vector<std::unique_ptr<Card> >cards) {
    for(int i = 0; i < cards.size(); i += 1){
        cards.push_back(std::move(cards.at(i)));
    }
}

Graveyard::~Graveyard() {

}

std::unique_ptr<Card> Graveyard::getCard(uint8_t cardNum) {
    std::unique_ptr<Card> ptr = std::move(cards.at((int)cardNum));
    cards.erase(cards.begin() + cardNum);
    return ptr;  
}

uint8_t Graveyard::getLenght() const {
    return (uint8_t)cards.size();
}

void Graveyard::add(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}