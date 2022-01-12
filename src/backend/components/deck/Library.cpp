//
// Created by houssem on 04/01/2022.
//

#include "Library.h"
#include <stdlib.h>

Library::Library(std::vector<std::unique_ptr<Card> > cards) {
    for(int i = 0; i < cards.size(); i += 1){
        std::unique_ptr<Card> newCard = std::move(cards.at(i));
        stack.push(newCard);
    }
    shuffle();
}


void Library::shuffle(){
    std::unique_ptr<Card> ptr;
    std::vector<std::unique_ptr<Card> > cards;
    do
    {
        ptr = std::move(getTopCard());
        if(ptr != nullptr) cards.push_back(ptr);
    } while (ptr != nullptr);

    while(cards.size() > 0){
        int rand = std::rand()%cards.size();
        std::unique_ptr<Card> newCard = std::move(cards.at(rand));
        cards.erase(cards.begin() + rand);
        stack.push(newCard);
    }    
    
}

Library::~Library() {

}

std::unique_ptr<Card> Library::getTopCard() {
    std::unique_ptr<Card> ptr = std::move(stack.top());
    stack.pop();
    return ptr;
}

Card* Library::getCard(uint8_t cardNum) {
    return stack.top().get();
}

uint8_t Library::getLenght() const {
    return (uint8_t)stack.size();
}