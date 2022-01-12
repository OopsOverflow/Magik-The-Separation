//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_LIBRARY_H
#define MAGIK_LIBRARY_H

#include <stack>
#include "Deck.h"

class Library : public Deck {
public : 
    Library(std::vector<std::unique_ptr<Card> >cards);
    ~Library();

    void shuffle();
    std::unique_ptr<Card> getTopCard(); //Non const bc remove top stack
    Card* getCard(uint8_t cardNum);
    uint8_t getLenght() const;

private :
    std::stack<std::unique_ptr<Card> > stack;

};


#endif //MAGIK_LIBRARY_H
