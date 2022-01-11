//
// Created by pierre on 05/01/2022.
//

#ifndef MAGIK_PLAYER_H
#define MAGIK_PLAYER_H
#include "string"
#include "../deck/Battlefield.h"
#include "../deck/Exile.h"
#include "../deck/Graveyard.h"
#include "../deck/Hand.h"
#include "../deck/Library.h"

class Player {
public :
    Player(std::string name, std::vector<std::unique_ptr<Card> >deck);
    ~Player();

    std::string getName() const;
    uint64_t getId() const;
    int8_t getHp() const;
    void draw(uint8_t numberOfCards = 1);

    Battlefield getBattlefield() const;
    Hand getHand() const;
    Graveyard getGraveyard() const;
    Library getLibrary() const;
    Exile getExile() const;

    void allowCastInstant();
    bool wantCastInstant() const;

private :
    std::string name;
    uint64_t id;
    int8_t hp;

    Battlefield battlefield;
    Hand hand;
    Graveyard graveyard;
    Library library;
    Exile exile;

    bool canCastInstant;

    static uint64_t newId;
};


#endif //MAGIK_PLAYER_H
