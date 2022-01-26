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

    uint16_t getLength() const;
    std::string toJson();

    std::unique_ptr<Card> popCard(uint16_t cardId);
    void add(std::unique_ptr<Card> card);
    Card* seekCard(uint16_t cardId);

    std::vector<Creature*> getCreatures();
    std::vector<Land*> getLands();
    std::vector<Sorcery*> getSorceries();
    std::vector<Enchantement*> getEnchantements();
    std::vector<Instant*> getInstants();

    std::unique_ptr<Creature> summonCreature(uint16_t id);
    std::unique_ptr<Land> summonLand(uint16_t id);
    std::unique_ptr<Sorcery> summonSorcery(uint16_t id);
    std::unique_ptr<Enchantement> summonEnchantement(uint16_t id);
    std::unique_ptr<Instant> summonInstant(uint16_t id);

private : 
    std::vector<std::unique_ptr<Creature> > creatures;
    std::vector<std::unique_ptr<Land> > lands;
    std::vector<std::unique_ptr<Sorcery> > sorceries;
    std::vector<std::unique_ptr<Enchantement> > enchantements;
    std::vector<std::unique_ptr<Instant> > instants;

};


#endif //MAGIK_HAND_H
