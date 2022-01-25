//
// Created by houssem on 04/01/2022.
//

#include "Library.h"
#include <stdlib.h>
#include <random>
#include <algorithm>

Library::Library() {
    
}


void Library::shuffle(){
    std::random_device rd; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(stack), std::end(stack), rng); 
    
}

Library::~Library() {

}

std::unique_ptr<Card> Library::getTopCard() {
    std::unique_ptr<Card> ptr = std::move(stack.at(stack.size()-1)); //TODO verify if not empty
    stack.pop_back();
    return ptr;
}

uint16_t Library::getLength() const {
    return (uint16_t)stack.size();
}

void Library::add(std::unique_ptr<Card> card) {
    std::cout<<"Added " <<card.get()->getName()<< " to library"<<std::endl;
    stack.push_back(std::move(card));
}

// std::vector<Card*> Library::getCards() {
//     std::vector<Card*> result;
//     for(auto& card : stack)
//         result.push_back(card.get());
//     return result;
// }