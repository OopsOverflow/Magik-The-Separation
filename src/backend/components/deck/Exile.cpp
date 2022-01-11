//
// Created by houssem on 04/01/2022.
//

#include "Exile.h"

Exile::Exile(std::vector<std::unique_ptr<Card> >cards) {
    for(int i = 0; i < cards.size(); i += 1){
        cards.push_back(std::move(cards.at(i)));
    }
}

Exile::~Exile() {

}

std::unique_ptr<Card> Exile::getCard(uint8_t cardNum) {
    std::unique_ptr<Card> ptr = std::move(cards.at((int)cardNum));
    return ptr;  
}

uint8_t Exile::getLenght() const {
    return (uint8_t)cards.size();
}