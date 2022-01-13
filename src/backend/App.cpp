//
// Created by houssem on 04/01/2022.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "server/Server.h"

//TODO remove sfml from cmake


int main(){
    srand(time(nullptr));
    Server server;    

    while(server.getPlayer1()->getHp() > 0 && server.getPlayer2()->getHp() > 0){
        server.solvePhase();
        
    }
        return 0;
}