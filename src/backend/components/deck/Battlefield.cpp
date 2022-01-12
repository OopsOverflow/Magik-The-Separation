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

std::unique_ptr<Card> Battlefield::popCard(uint8_t cardNum) {
    std::unique_ptr<Card> ptr = std::move(cards.at((int)cardNum));
    cards.erase(cards.begin() + cardNum);
    return ptr;  
}

Card* Battlefield::getCard(uint8_t cardNum) {
    return cards.at((int)cardNum).get();
}

int8_t Battlefield::getCardIndex(Card* card) {
    int8_t i = 0;
    for(i; i < cards.size(); i += 1) {
        if(cards.at(i).get() == card)
            return i;
    }
    return -1;
}

uint8_t Battlefield::getLenght() const {
    return (uint8_t) cards.size();
}


void Battlefield::add(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}

void Battlefield::unTap(uint8_t cardNum){
    getCard(cardNum)->unTap();
}    