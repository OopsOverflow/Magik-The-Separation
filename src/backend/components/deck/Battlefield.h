//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_BATTLEFIELD_H
#define MAGIK_BATTLEFIELD_H

#include <vector>
#include "Deck.h"


class Battlefield : public Deck{
public : 
    Battlefield();
    ~Battlefield();

    uint8_t getLength() const;

    void add(std::unique_ptr<Card> card);
    std::unique_ptr<Card> popCard(uint8_t cardId);
    Card* getCard(uint8_t cardId);

    std::vector<Creature*> getCreatures();
    std::vector<Land*> getLands();

private : 
    std::vector<std::unique_ptr<Creature> > creatures;
    std::vector<std::unique_ptr<Land> > lands;
};


#endif //MAGIK_BATTLEFIELD_H
