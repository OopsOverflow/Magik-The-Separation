//
// Created by houssem on 04/01/2022.
//

#include "Hand.h"


Hand::Hand(std::vector<std::unique_ptr<Card> >cards) {
    for(int i = 0; i < cards.size(); i += 1){
        cards.push_back(std::move(cards.at(i)));
    }
}


Hand::~Hand() {
}

std::unique_ptr<Card> Hand::getCard(uint8_t cardNum) {
    std::unique_ptr<Card> ptr = std::move(cards.at((int)cardNum));
    return ptr;    
}
uint8_t Hand::getLenght() const {
    return (uint8_t)cards.size();
}

void Hand::add(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}