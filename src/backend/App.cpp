//
// Created by houssem on 04/01/2022.
//
#include <iostream>
#include "components/player/Player.h"
#include "game/GameAction.h"
#include "backend/components/card/Creature.h"

#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>


int main(){

        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Blue);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

        return 0;

//
//    srand(time(nullptr));
//
//    std::cout << "Here" << std::endl;
//    std::vector<std::unique_ptr<Card> >deckPlayer1;
//    std::vector<std::unique_ptr<Card> >deckPlayer2;
//
//    std::shared_ptr<Stack> stack = std::make_shared<Stack>();
//
//    Player player1("Bob", deckPlayer1, stack);
//    Player player2("Henri", deckPlayer2, stack);
//
//    player1.setOpponent(&player2);
//    player2.setOpponent(&player1);
//
//    Player* playerToPlay = &player1;
//    Player* opponent = &player2;
//    int turn = 0;
//
//
//
//    while(player1.getHp() > 0 && player2.getHp() > 0){
//        turn +=1 ;
//        /* BEGINNING PHASE */
//
//        //You untap all your tapped permanents
//        playerToPlay->unTapAll();
//
//
//        //Players can cast instants and activate abilities
//        playerToPlay->castSpellOrAbility(true);
//        stack.get()->solve();
//        if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
//
//        //Player must draw a card from his library
//        if(turn > 1) {
//            playerToPlay->draw();
//            playerToPlay->castSpellOrAbility(true);
//            stack.get()->solve();
//            if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
//        }
//
//        /* FIRST MAIN PHASE */
//
//        //You can cast any number of sorceries, instants, creatures, artifacts, enchantments, and planeswalkers, and you can activate abilities
//        bool hasPlayedLand = false;
//        while(playerToPlay->getHand()->getLenght() > 0) {
//            if(!hasPlayedLand){
//                playerToPlay->summonCard(0);//TODO choose card to play
//                opponent->castSpellOrAbility(true);
//                stack.get()->solve();
//                if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
//            }else{
//
//            }
//        }
//
//        /* COMBAT PHASE */
//        //Beginning of combat step
//        playerToPlay->castSpellOrAbility(true);
//        stack.get()->solve();
//
//        //Declare attackers step
//        std::vector<Creature*> attackingCards;
//        while(playerToPlay->getBattlefield()->getLenght() > 0) {
//            Creature* attackingCard = dynamic_cast<Creature*>(playerToPlay->getBattlefield()->getCard(0));//TODO choose cards to play
//            if(attackingCard)attackingCards.push_back(attackingCard);
//        }
//        if(attackingCards.size() > 0) {
//            playerToPlay->castSpellOrAbility(true);
//            stack.get()->solve();
//            if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
//
//            //Declare blockers step
//            std::vector<std::vector<Creature*> > blockingCards(attackingCards.size());
//            while(opponent->getBattlefield()->getLenght() > 0) {
//            //TODO choose cards which block
//                Creature* blockingCard = dynamic_cast<Creature*>(opponent->getBattlefield()->getCard(0));
//                if(blockingCard)blockingCards.at(0).push_back(blockingCard); //TODO block Nth-card
//            }
//            playerToPlay->castSpellOrAbility(true);
//            stack.get()->solve();
//            if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
//
//            //Combat damage step
//            for(int i = 0; i < attackingCards.size(); i += 1) {
//                if(blockingCards.at(i).size() > 0) {
//
//                    for(int j = 0; i < blockingCards.at(i).size(); j += 1) {
//                        if(attackingCards.at(i)->getTempThougness() > 0) {
//                            blockingCards.at(i).at(j)->block(attackingCards.at(i));
//                            if(blockingCards.at(i).at(j)->getTempThougness() <= 0) {
//                                int8_t deleteIndex = opponent->getBattlefield()->getCardIndex(dynamic_cast<Card*>(blockingCards.at(i).at(j)));//TODO high risk concerning pointer here
//                                std::unique_ptr<Card> card = opponent->getBattlefield()->popCard(deleteIndex);
//                                opponent->getGraveyard()->add(std::move(card));
//                            }
//                        }
//                    }
//                }else{
//                    opponent->takeDamage(attackingCards.at(i)->getPower());
//                    if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
//                }
//            }
//            playerToPlay->castSpellOrAbility(true);
//            stack.get()->solve();
//
//            if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
//        }
//
//        //End of combat step
//        playerToPlay->castSpellOrAbility(true);
//
//        /* SECOND MAIN PHASE */
//        while(playerToPlay->getHand()->getLenght() > 0) {
//            if(!hasPlayedLand){
//                playerToPlay->summonCard(0);//TODO choose card to play
//                opponent->castSpellOrAbility(true);
//                stack.get()->solve();
//                if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
//            }else{
//
//            }
//        }
//
//        /* ENDING PHASE */
//        //End step
//        playerToPlay->castSpellOrAbility(true);
//        stack.get()->solve();
//        if(player1.getHp() <= 0 && player2.getHp() <= 0) continue;
//
//        //Cleanup step
//        while(playerToPlay->getHand()->getLenght() > 7) {
//            std::unique_ptr<Card> card = playerToPlay->getHand()->popCard(0);//TODO choose cards to throw
//            playerToPlay->getGraveyard()->add(std::move(card));
//        }
//
//    }

    //TODO reset all creatures thougness
    std::cout << "Hello Pignoul" << std::endl;
    return 0;
}