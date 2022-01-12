//
// Created by pierre on 11/01/2022.
//

#include "Stack.h"
#include <stdlib.h>

Stack::Stack() {

}

Stack::~Stack() {

}

std::unique_ptr<Card> Stack::getTopCard() {
    std::unique_ptr<Card> ptr = std::move(stack.top());
    stack.pop();
    return ptr;
}

Card* Stack::getCard(uint8_t cardNum) {
    return stack.top().get();
}

uint8_t Stack::getLenght() const {
    return (uint8_t)stack.size();
}

void Stack::add(std::unique_ptr<Card> card) {
    stack.push(std::move(card));
}

void Stack::solve() {
    
}