//
// Created by pierre on 11/01/2022.
//

#include "Stack.h"
#include <stdlib.h>

Stack::Stack() {
    std::cout<<"Stack created"<<std::endl;
}

Stack::~Stack() {

}

std::pair<std::unique_ptr<Card>, Player*> Stack::getTopPair() {
    std::pair<std::unique_ptr<Card>, Player*> result = {std::move(stack.at(stack.size() - 1).first), stack.at(stack.size() - 1).second};
    stack.pop_back();
    return result;
}

uint8_t Stack::getLength() const {
    return (uint8_t)stack.size();
}

void Stack::add(std::pair<std::unique_ptr<Card>, Player*> card) {
    stack.push_back({std::move(card.first), card.second});
}

void Stack::display() {
    std::cout<<"---Stack "<<std::endl;
    for(int i = 0; i< getLength(); i += 1) {
        std::cout<< stack.at(i).second->getName() << " - " << stack.at(i).first.get()->getName()<< std::endl;
    }
}