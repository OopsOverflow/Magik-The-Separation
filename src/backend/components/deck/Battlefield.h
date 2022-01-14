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

    std::unique_ptr<Card> popCard(uint8_t cardId);
    Card* getCard(uint8_t cardId);
    uint8_t getLenght() const;

    void unTap(uint8_t cardNum);  

    void addCreature(std::unique_ptr<Creature> card);
    void addLand(std::unique_ptr<Land> card);
    void addEnchantement(std::unique_ptr<Enchantement> card, Creature* creature);

private : 
    std::vector<std::unique_ptr<Creature> > creatures;
    std::vector<std::unique_ptr<Land> > lands;
};


#endif //MAGIK_BATTLEFIELD_H
