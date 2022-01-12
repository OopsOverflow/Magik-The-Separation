//
// Created by houssem on 04/01/2022.
//

#include "Hand.h"


Hand::Hand() {
}

Hand::~Hand() {
}

std::unique_ptr<Card> Hand::popCard(uint8_t cardNum) {
    std::unique_ptr<Card> ptr = std::move(cards.at((int)cardNum));
    cards.erase(cards.begin() + cardNum);
    return ptr;    
}

Card* Hand::getCard(uint8_t cardNum) {
    return cards.at((int)cardNum).get();
}

uint8_t Hand::getLenght() const {
    return (uint8_t)cards.size();
}


void Hand::add(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}