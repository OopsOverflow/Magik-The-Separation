//
// Created by houssem on 04/01/2022.
//
#include <iostream>
#include "components/player/Player.h"
#include "game/GameAction.h"

#include <stdlib.h>
#include <time.h>

Player player1;
Player player2;

void playerCastInstant() {
    player1.allowCastInstant();
    player2.allowCastInstant();
    while (player1.wantCastInstant() && player2.wantCastInstant())
        {
              //TODO allow player to cast instant -> player.canstingInstant()
        }    
}


int main(){
    srand(time(NULL));
    std::vector<std::unique_ptr<Card> >deckPlayer1;
    std::vector<std::unique_ptr<Card> >deckPlayer2;
    Stack stack;

    Player player1("Bob", deckPlayer1, std::make_shared<Stack>(stack));
    Player player2("Henri", deckPlayer2, std::make_shared<Stack>(stack));

    Player* playerToPlay = &player1;
    int turn = 0;
    while(player1.getHp() > 0 && player2.getHp() > 0){
        turn +=1 ;
        /* BEGINNING PHASE */

        //You untap all your tapped permanents
        for(int i = 0; i< playerToPlay->getBattlefield().getLenght(); i += 1){
            playerToPlay->getBattlefield().unTap(i);
        }

        //Players can cast instants and activate abilities
        playerCastInstant();
        if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;

        //Player must draw a card from his library 
        if(turn > 1) {
            playerToPlay->draw();
            if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
            playerCastInstant();
            if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
        }

        /* FIRST MAIN PHASE */

        //You can cast any number of sorceries, instants, creatures, artifacts, enchantments, and planeswalkers, and you can activate abilities
        bool hasPlayedLand = false;
        while(playerToPlay->getHand().getLenght() > 0) {
            playerToPlay->summonCard(0);

        }
        

    }

    std::cout << "Hello Pignoul" << std::endl;
    return 0;
}