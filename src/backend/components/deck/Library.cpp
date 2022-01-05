//
// Created by houssem on 04/01/2022.
//

#include "Library.h"
#include <stdlib.h>

Library::Library(std::vector<std::unique_ptr<Card> > cards) {
    while(cards.size() > 0){
        int rand = std::rand() % cards.size();
        std::unique_ptr<Card> newCard = cards.at(rand);
        cards.erase(cards.begin() + rand);
        stack.push(newCard);
    }
}

Library::~Library() {

}

std::unique_ptr<Card> Library::getTopCard() {
    return stack.pop();
}

uint8_t Library::getLenght() const {
    return (uint8_t)stack.size();
}