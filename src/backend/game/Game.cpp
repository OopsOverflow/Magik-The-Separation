//
// Created by pierre on 13/01/2022.
//

#include "Game.h"

Game::Game() : stack(std::make_shared<Stack>()), player1("Bob", deckPlayer1, stack), player2("Henri", deckPlayer2, stack){

}

Game::~Game() {

}

void Game::solvePhase() {
    GameAction& action = GameAction::getInst();
    switch (action.getPhase())
    {
    /* BEGINNING PHASE */
    case Phase::UNTAP_STEP:
        //Choose player to play
        if(action.getTurn() % 2 == 1) {
            playerToPlay = &player1;
            opponent = &player2;
        }else{
            playerToPlay = &player2;
            opponent = &player1;
        }

        //You untap all your tapped permanents
        playerToPlay->unTapAll();

        break;

    case Phase::UPKEEP_STEP:
        //TODO trigger beginnig of unkeep step

        //Players can cast instants and activate abilities
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;

    case Phase::DRAW_STEP:

       //Player must draw a card from his library        
        playerToPlay->draw();
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;


    /* FIRST MAIN PHASE */  
    case Phase::FIRST_MAIN_PHASE:
        action.hasPlayedLand = false;

        //You can cast any number of sorceries, instants, creatures, artifacts, enchantments, and planeswalkers, and you can activate abilities
        if(true){//wantToPlaySmth
            playerToPlay->summonCard(0);//TODO choose card to play
            if(stack->getLenght()>0)//If it's a land, nothing will be on the stack
                while(opponent->castSpellOrAbility() || playerToPlay->castSpellOrAbility());
            stack.get()->solve();
        }else{
        }

        break;

    
    /* COMBAT PHASE */
    case Phase::BEGINNING_OF_COMBAT_STEP:

        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;

    case Phase::DECLARE_ATTACKER_STEP:
        playerToPlay->setAttackingCards();
        if(playerToPlay->getAttackingCards().size() > 0)
            while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;
    case Phase::DECLARE_BLOCKER_STEP:
        opponent->setBlockingCards(playerToPlay->getAttackingCards());
        if(playerToPlay->getAttackingCards().size() > 0)
            while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;

    
    case Phase::COMBAT_DAMAGE_STEP:
        for(int i = 0; i < playerToPlay->getAttackingCards().size(); i += 1) {
            if(opponent->getBlockingCards().at(i).size() > 0) {

                for(int j = 0; i < opponent->getBlockingCards().at(i).size(); j += 1) {

                    if(playerToPlay->getAttackingCards().at(i)->getTempThougness() > 0) {

                        opponent->getBlockingCards().at(i).at(j)->block(playerToPlay->getAttackingCards().at(i));
                        if(opponent->getBlockingCards().at(i).at(j)->getTempThougness() <= 0) {
                            opponent->killCard(opponent->getBlockingCards().at(i).at(j));
                        }
                    }
                }
            }else{
                opponent->takeDamage(playerToPlay->getAttackingCards().at(i)->getPower());
            }
        }
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;
    case Phase::END_OF_COMBAT_STEP:
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;

    /* SECOND MAIN PHASE */
    case Phase::SECOND_MAIN_PHASE:
        if(true){//wantToPlaySmth
            playerToPlay->summonCard(0);//TODO choose card to play
            if(stack->getLenght()>0)//If it's a land, nothing will be on the stack
                while(opponent->castSpellOrAbility() || playerToPlay->castSpellOrAbility());
            stack.get()->solve();
        }else{
        }
        
        break;

    /* ENDING PHASE */
    case Phase::END_STEP:
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;
    
    case Phase::CLEANUP_STEP:
        while(playerToPlay->getHand()->getLenght() > 7) {
            Card* chosenOne;
            playerToPlay->killCard(chosenOne);
        }

        break;

    default:
        //! ERROR
        break;
    }

    action.nextPhase();

}

void Game::resolveEvent(Event event) {
    for(uint8_t i = 0; playerToPlay->getBattlefield()->getLenght(); i += 1) {
        Creature* card =  dynamic_cast<Creature*> (playerToPlay->getBattlefield()->getCard(i));
        if(card) {
            std::vector<std::function<void(Event)> > abilities = card->getTriggerAbilities();
            for(uint8_t j = 0; j < abilities.size(); j += 1) {
                abilities.at(i)(event); //TODO abilities affect game
            }
        }
    }
}
