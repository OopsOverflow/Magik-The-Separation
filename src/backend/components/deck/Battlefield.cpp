//
// Created by houssem on 04/01/2022.
//

#include "Battlefield.h"


Battlefield::Battlefield(std::vector<std::unique_ptr<Card> >cards) {
    for(int i = 0; i < cards.size(); i += 1){
        cards.push_back(std::move(cards.at(i)));
    }
}

Battlefield::~Battlefield() {

}

std::unique_ptr<Card> Battlefield::getCard(uint8_t cardNum) {
    std::unique_ptr<Card> ptr = std::move(cards.at((int)cardNum));
    return ptr;  
}

uint8_t Battlefield::getLenght() const {
    return (uint8_t)cards.size();
}

void Battlefield::unTap(uint8_t cardNum){
    std::unique_ptr<Card> card = getCard(cardNum);
    card->unTap();
    cards.at((int)cardNum) = std::move(card);
}    