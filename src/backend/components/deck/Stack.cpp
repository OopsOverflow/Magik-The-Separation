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

std::unique_ptr<Card> Stack::getTopCard() {
    std::unique_ptr<Card> ptr = std::move(stack.at(stack.size() - 1));
    stack.pop_back();
    return ptr;
}

uint8_t Stack::getLength() const {
    return (uint8_t)stack.size();
}

void Stack::add(std::unique_ptr<Card> card) {
    stack.push_back(std::move(card));
}

void Stack::solve() {
    
}

void Stack::display() {
    std::cout<<"---Stack "<<std::endl;
    for(int i = 0; i< getLength(); i += 1) {
        std::cout<< i << " - " << stack.at(i).get()->getName()<< std::endl;
    }
}