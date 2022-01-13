//
// Created by pierre on 13/01/2022.
//

#ifndef MAGIK_SERVER_H
#define MAGIK_SERVER_H

#include <vector>

#include "../game/GameAction.h"
#include "../components/player/Player.h"
#include "../components/deck/Stack.h"

class Server{
public : 
    Server();
    ~Server();

    Player* getPlayer1();
    Player* getPlayer2();

    void solvePhase();
    void endOfPhase();

private : 
    
    Player player1;
    Player player2;

    std::shared_ptr<Stack> stack;

    std::vector<std::unique_ptr<Card> >deckPlayer1;
    std::vector<std::unique_ptr<Card> >deckPlayer2;

    Player* playerToPlay;
    Player* opponent;

};


#endif //MAGIK_SERVER_H
