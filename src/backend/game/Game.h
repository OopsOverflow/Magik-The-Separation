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
    void chooseCards();
    void initGame();


private : 
    //Be careful ! Order is important for initialisation
    std::shared_ptr<Stack> stack;
    
    Player player1;
    Player player2;



    Player* playerToPlay;
    Player* opponent;

};


#endif //MAGIK_GAME_H
