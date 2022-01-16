//
// Created by houssem on 04/01/2022.
//

#include "Library.h"
#include <stdlib.h>

Library::Library() {
    
}


void Library::shuffle(){
    std::unique_ptr<Card> ptr;
    std::vector<std::unique_ptr<Card>> cards;
    do
    {
        ptr = std::move(getTopCard());
        if(ptr != nullptr) cards.push_back(std::move(ptr));
    } while (ptr != nullptr);

    while(cards.size() > 0){
        int rand = std::rand()%cards.size();
        std::unique_ptr<Card> newCard = std::move(cards.at(rand));
        cards.erase(cards.begin() + rand);
        stack.push_back(std::move(newCard));
    }    
    
}

Library::~Library() {

}

std::unique_ptr<Card> Library::getTopCard() {
    std::unique_ptr<Card> ptr = std::move(stack.at(stack.size()-1)); //TODO verify if not empty
    stack.pop_back();
    return ptr;
}

uint8_t Library::getLenght() const {
    return (uint8_t)stack.size();
}

void Library::add(std::unique_ptr<Card> card) {
    std::cout<<"Added " <<card.get()->getName()<< " to library"<<std::endl;
    stack.push_back(std::move(card));
}

std::vector<Card*> Library::getCards() {
    std::vector<Card*> result;
    for(auto const& card : stack)
        result.push_back(card.get());
    return result;
}