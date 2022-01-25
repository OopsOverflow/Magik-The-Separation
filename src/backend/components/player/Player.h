//
// Created by pierre on 05/01/2022.
//

#ifndef MAGIK_PLAYER_H
#define MAGIK_PLAYER_H
#include <string>
#include "../deck/Battlefield.h"
#include "../deck/Graveyard.h"
#include "../deck/Hand.h"
#include "../deck/Library.h"

class Player {
public :
    Player(std::string name);
    ~Player();

    std::string getName() const;
    uint64_t getId() const;
    int getHp() const;   
    
    //actions
    void draw();
    void unTapAll();
    void takeDamage(int amount);
    void heal(int amount);

    Card* seekCard(uint16_t cardId);
    std::unique_ptr<Card> playCard(uint16_t cardId);

    Battlefield* getBattlefield();
    Hand* getHand();
    Graveyard* getGraveyard();
    Library* getLibrary();

    void killCard(uint16_t cardId);
    std::vector<uint16_t> getCastableInstantsOrAbilities();
    std::vector<uint16_t> getPlayableCards(bool hasPlayedLand);


private :
    std::string name;
    uint64_t id;
    int hp;

    Battlefield battlefield;
    Hand hand;
    Graveyard graveyard;
    Library library;

    static uint64_t newId;
    

};


#endif //MAGIK_PLAYER_H
