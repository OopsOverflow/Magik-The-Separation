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
#include "../deck/Stack.h"

class Player {
public :
    Player(std::string name, std::vector<std::unique_ptr<Card> >deck, std::shared_ptr<Stack> stack);
    ~Player();

    std::string getName() const;
    uint64_t getId() const;
    int8_t getHp() const;
    void setOpponent(Player* player);    
    
    //actions
    void draw(uint8_t numberOfCards = 1);
    void summonCard(uint8_t cardNumber);
    void unTapAll();
    void takeDamage(uint8_t amount);

    void castSpellOrAbility(bool hasCasted);

    Battlefield getBattlefield() const;
    Hand getHand() const;
    Graveyard getGraveyard() const;
    Library getLibrary() const;
    Exile getExile() const;



private :
    std::string name;
    uint64_t id;
    int8_t hp;

    Player* opponent;

    Battlefield battlefield;
    Hand hand;
    Graveyard graveyard;
    Library library;
    Exile exile;

    bool canCastInstant;

    static uint64_t newId;

    std::shared_ptr<Stack> stack;
};


#endif //MAGIK_PLAYER_H
