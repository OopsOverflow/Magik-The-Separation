//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_LIBRARY_H
#define MAGIK_LIBRARY_H

#include <vector>
#include "Deck.h"

class Library : public Deck {
public : 
    Library();
    ~Library();

    void shuffle();
    std::unique_ptr<Card> getTopCard(); //Non const bc remove top stack
    //Card* getCard(uint8_t cardNum);
    uint8_t getLenght() const;
    void add(std::unique_ptr<Card> card);

    std::vector<Card*> getCards();

private :

    std::vector<std::unique_ptr<Card> > stack;
};


#endif //MAGIK_LIBRARY_H
