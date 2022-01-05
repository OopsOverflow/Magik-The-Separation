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
    Player(std::string name);
    ~Player();
    std::string getName() const;
    uint64_t getId() const;

private :
    std::string name;
    uint64_t id;
    
    Battlefield battlefield;
    Hand hand;
    Graveyard graveyard;
    Library library;
    Exile exile;

    static uint64_t newId;
};


#endif //MAGIK_PLAYER_H
