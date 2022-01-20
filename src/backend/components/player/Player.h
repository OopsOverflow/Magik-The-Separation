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
#include "../card/Creature.h"

class Player {
public :
    Player(std::string name);
    ~Player();

    std::string getName() const;
    uint64_t getId() const;
    int8_t getHp() const;   
    
    //actions
    void draw();
    void unTapAll();
    void takeDamage(uint8_t amount);
    Card* seekCard(uint8_t id);
    std::unique_ptr<Card> playCard(uint8_t id);

    Battlefield* getBattlefield();
    Hand* getHand();
    Graveyard* getGraveyard();
    Library* getLibrary();

    void killCard(Card* cardToKill);
    std::vector<uint8_t> getCastableInstantsOrAbilities();
    std::vector<uint8_t> getPlayableCards(bool hasPlayedLand);

    void setAttackingCreatures();
    std::vector<uint8_t> getAttackingCreatures();

    void setBlockingCreatures(std::vector<Creature *> attacking);
    std::vector<std::vector<uint8_t> > getBlockingCreatures();

private :
    std::string name;
    uint64_t id;
    int8_t hp;

    Battlefield battlefield;
    Hand hand;
    Graveyard graveyard;
    Library library;


    bool canCastInstant;

    static uint64_t newId;

    std::vector<uint8_t> attackingCreatures;
    std::vector<std::vector<uint8_t> > blockingCreatures;

    
    

};


#endif //MAGIK_PLAYER_H
