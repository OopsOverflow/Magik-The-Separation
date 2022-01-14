//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_HAND_H
#define MAGIK_HAND_H

#include <vector>
#include "Deck.h"

class Hand : public Deck {
public : 
    Hand();
    ~Hand();

    std::unique_ptr<Card> popCard(uint8_t cardId);
    Card* getCard(uint8_t cardId);
    uint8_t getLenght() const;

    void add(std::unique_ptr<Card> card);

private : 
    std::vector<std::unique_ptr<Creature> > creatures;
    std::vector<std::unique_ptr<Land> > lands;
    std::vector<std::unique_ptr<Sorcery> > sorceries;
    std::vector<std::unique_ptr<Enchantement> > enchantements;
    std::vector<std::unique_ptr<Instant> > instants;

};


#endif //MAGIK_HAND_H
