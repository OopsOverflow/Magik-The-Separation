//
// Created by houssem on 04/01/2022.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <functional>

#include "game/Game.h"

//TODO remove sfml from cmake


int main(){
    srand(time(nullptr));
    Game game;    

    while(game.getPlayer1()->getHp() > 0 && game.getPlayer2()->getHp() > 0){
        game.solvePhase();
        
    }
        return 0;
}
