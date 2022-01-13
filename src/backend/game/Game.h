//
// Created by pierre on 13/01/2022.
//

#ifndef MAGIK_GAME_H
#define MAGIK_GAME_H

#include <vector>

#include "GameAction.h"
#include "../components/player/Player.h"
#include "../components/deck/Stack.h"
#include "../components/card/Card.h"

class Game{
public : 
    Game();
    ~Game();

    Player* getPlayer1();
    Player* getPlayer2();

    void solvePhase();
    void endOfPhase();

    void resolveEvent(Event event);

private : 
    
    Player player1;
    Player player2;

    std::shared_ptr<Stack> stack;

    std::vector<std::unique_ptr<Card> >deckPlayer1;
    std::vector<std::unique_ptr<Card> >deckPlayer2;

    Player* playerToPlay;
    Player* opponent;

};


#endif //MAGIK_GAME_H
