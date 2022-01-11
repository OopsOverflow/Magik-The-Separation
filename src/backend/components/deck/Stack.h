//
// Created by pierre on 11/01/2022.
//

#ifndef MAGIK_STACK_H
#define MAGIK_STACK_H

#include <stack>

#include "Deck.h"
class Stack : public Deck {
public : 
    Stack();
    ~Stack();

    std::unique_ptr<Card> getTopCard(); //Non const bc remove top stack
    uint8_t getLenght() const;
    void add(std::unique_ptr<Card> card);

private :
    std::stack<std::unique_ptr<Card> > stack;

};


#endif //MAGIK_STACK_H
