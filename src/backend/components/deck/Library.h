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

    Library(Library const&) = delete;
    Library& operator=(Library const&) = delete;

    uint8_t getLength() const;

    void shuffle();
    std::unique_ptr<Card> getTopCard();
    void add(std::unique_ptr<Card> card);

private :

    std::vector<std::unique_ptr<Card> > stack;
};


#endif //MAGIK_LIBRARY_H
