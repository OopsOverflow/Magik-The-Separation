//
// Created by pierre on 11/01/2022.
//

#ifndef MAGIK_STACK_H
#define MAGIK_STACK_H

#include <vector>

#include "Deck.h"
#include "../player/Player.h"
class Stack : public Deck {
public : 
    Stack();
    ~Stack();

    Stack(Stack const&) = delete;
    Stack& operator=(Stack const&) = delete;

    uint8_t getLength() const;

    std::pair<std::unique_ptr<Card>, Player*> getTopPair();
    void add(std::pair<std::unique_ptr<Card>, Player*> card);

    void display();
private :
    std::vector<std::pair<std::unique_ptr<Card>, Player*> > stack;

};


#endif //MAGIK_STACK_H
