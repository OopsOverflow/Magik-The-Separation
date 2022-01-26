//
// Created by pierre on 13/01/2022.
//

#ifndef MAGIK_GAME_H
#define MAGIK_GAME_H

#include <vector>

#include "GameAction.h"
#include "server/WebSocketServer.h"
#include "../components/player/Player.h"
#include "../components/deck/Stack.h"
#include "../components/card/Card.h"

Json::Value& operator<<(Json::Value& val, const std::string& str)
{
    Json::Reader reader;
    if(!reader.parse(str, val, false)) std::runtime_error("Parse Error : " + str);
    return val;
}

class Game{
public : 
    Game(WebsocketServer* server);
    ~Game();

    Player* getPlayer1();
    Player* getPlayer2();

    void solvePhase();
    void chooseCards();
    void initGame();

private : 
    void endOfPhase();

    void resolveEvent(Event event);


    bool castInstantsOrAbilities(Player* castingPlayer, bool lastHasPlayed = true);
    void solveStack();

    //Be careful ! Order is important for initialisation
    std::shared_ptr<Stack> stack;
    
    Player player1;
    Player player2;

    WebsocketServer* server;

    Player* playerToPlay;
    Player* opponent;

};


#endif //MAGIK_GAME_H
