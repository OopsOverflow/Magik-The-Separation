//
// Created by houssem on 04/01/2022.
//
#include <iostream>
#include "components/player/Player.h"
#include "game/GameAction.h"

#include <stdlib.h>
#include <time.h>

int main(){

    srand(time(NULL));
    Player player1("Bob");
    Player player2("Henri");

    Player* playerToPlay = &player1;
    while(player1.getHp() > 0 && player2.getHp() > 0){
        Phase phase = GameAction::getInst().getPhase();


    }

    std::cout << "Hello Pignoul" << std::endl;
    return 0;
}