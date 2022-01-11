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
    std::vector<std::unique_ptr<Card> >deckPlayer1;
    std::vector<std::unique_ptr<Card> >deckPlayer2;
    Stack stack;


    Player player1("Bob", deckPlayer1, std::make_shared<Stack>(stack));
    Player player2("Henri", deckPlayer2, std::make_shared<Stack>(stack));

    player1.setOpponent(&player2);
    player2.setOpponent(&player1);

    Player* playerToPlay = &player1;
    Player* opponent = &player2;
    int turn = 0;
    
    while(player1.getHp() > 0 && player2.getHp() > 0){
        turn +=1 ;
        /* BEGINNING PHASE */

        //You untap all your tapped permanents
        playerToPlay->unTapAll();


        //Players can cast instants and activate abilities
        playerToPlay->castSpellOrAbility(true);
        stack.solve();
        if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;

        //Player must draw a card from his library 
        if(turn > 1) {
            playerToPlay->draw();
            playerToPlay->castSpellOrAbility(true);
            stack.solve();
            if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
        }

        /* FIRST MAIN PHASE */

        //You can cast any number of sorceries, instants, creatures, artifacts, enchantments, and planeswalkers, and you can activate abilities
        bool hasPlayedLand = false;
        while(playerToPlay->getHand().getLenght() > 0) {
            if(!hasPlayedLand){
                playerToPlay->summonCard(0);//TODO choose card to play
                opponent->castSpellOrAbility(true);
                stack.solve();
            }else{

            }
        }
        
        /* COMBAT PHASE */
        //Beginning of combat step
        playerToPlay->castSpellOrAbility(true);
        stack.solve();

        //Declare attackers step
        std::vector<std::unique_ptr<Card> > attackingCards;
        while(playerToPlay->getBattlefield().getLenght() > 0) {
            std::unique_ptr<Card> card = playerToPlay->getBattlefield().getCard(0);//TODO choose cards to play
            attackingCards.push_back(std::move(card));
        }
        if(attackingCards.size() > 0) {
            playerToPlay->castSpellOrAbility(true);
            stack.solve();

            //Declare blockers step
            std::vector<std::vector<std::unique_ptr<Card> > > blockingCards(attackingCards.size());
            while(opponent->getBattlefield().getLenght() > 0) {
                std::unique_ptr<Card> card = opponent->getBattlefield().getCard(0);//TODO choose cards which block
                blockingCards.at(0).push_back(std::move(card)); //TODO block Nth-card
            }     
            playerToPlay->castSpellOrAbility(true);
            stack.solve();

            //Combat damage step
            //TODO solve combat
            playerToPlay->castSpellOrAbility(true);
            stack.solve();
        }

        //End of combat step
        playerToPlay->castSpellOrAbility(true);

        /* SECOND MAIN PHASE */
        while(playerToPlay->getHand().getLenght() > 0) {
            if(!hasPlayedLand){
                playerToPlay->summonCard(0);//TODO choose card to play
                opponent->castSpellOrAbility(true);
                stack.solve();
            }else{

            }
        }

        /* ENDING PHASE */
        //End step
        playerToPlay->castSpellOrAbility(true);
        stack.solve();

        //Cleanup step
        while(playerToPlay->getHand().getLenght() > 7) {
            std::unique_ptr<Card> card = playerToPlay->getHand().getCard(0);//TODO choose cards to throw
            playerToPlay->getGraveyard().add(std::move(card));
        }

    }

    std::cout << "Hello Pignoul" << std::endl;
    return 0;
}