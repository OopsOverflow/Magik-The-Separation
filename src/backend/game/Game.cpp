//
// Created by pierre on 13/01/2022.
//

#include "Game.h"
#include "../components/card/CardMaker.h"

#include <algorithm>

Game::Game() : stack(std::make_shared<Stack>()), player1("Bob", stack), player2("Henri", stack), playerToPlay(&player1), opponent(&player2) {
    std::cout<<"Game instance created"<<std::endl;
}

Game::~Game() {

}

void Game::solvePhase() {
    GameAction& action = GameAction::getInst();
    switch (action.getPhase())
    {
    /* BEGINNING PHASE */
    case Phase::UNTAP_STEP:
        std::cout<<"Untap Step"<<std::endl;
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
        
        action.nextPhase();
        break;

    case Phase::UPKEEP_STEP:
        std::cout<<"Upkeep Step"<<std::endl;
        //TODO trigger beginnig of unkeep step

        //Players can cast instants and activate abilities
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();
        
        action.nextPhase();
        break;

    case Phase::DRAW_STEP:
        std::cout<<"Draw Step"<<std::endl;

       //Player must draw a card from his library        
        playerToPlay->draw();
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();
        
        action.nextPhase();
        break;


    /* FIRST MAIN PHASE */  
    case Phase::FIRST_MAIN_PHASE:
        std::cout<<"First Main Phase"<<std::endl;
        {    
            action.hasPlayedLand = false;
            if(playerToPlay == &player1)
                std::cout<<"Player 1 "<<std::endl;
            else
                std::cout<<"Player 2 "<<std::endl;

            Hand* hand = playerToPlay->getHand();
            int idx = 0;
            if(!action.hasPlayedLand) {
                std::cout<<"Lands : "<<std::endl;
                for(int i = 0 ; i < hand->getLands().size(); i += 1) 
                    std::cout<< idx++ << " - " << hand->getLands().at(i)->getName()<<std::endl;
            }
            std::cout<<"Creatures : "<<std::endl;
            for(int i = 0 ; i < hand->getCreatures().size(); i += 1) 
                std::cout<< idx++ << " - " << hand->getCreatures().at(i)->getName()<<std::endl;
            std::cout<<"Enchantments : "<<std::endl;
            for(int i = 0 ; i < hand->getEnchantements().size(); i += 1) 
                std::cout<< idx++ << " - " << hand->getEnchantements().at(i)->getName()<<std::endl;
            std::cout<<"Instants : "<<std::endl;
            for(int i = 0 ; i < hand->getInstants().size(); i += 1) 
                std::cout<< idx++ << " - " << hand->getInstants().at(i)->getName()<<std::endl;
            std::cout<<"Sorceries : "<<std::endl;
            for(int i = 0 ; i < hand->getSorceries().size(); i += 1) 
                std::cout<< idx++ << " - " << hand->getSorceries().at(i)->getName()<<std::endl;

            //You can cast any number of sorceries, instants, creatures, artifacts, enchantments, and planeswalkers, and you can activate abilities
            char response = 0;
            while (response != 'y' && response != 'n')
            {

                std::cout<<"Do you want to play something ? (y/n) ";
                std::string str;
                std::cin>>str;
                response = str[0];
            }
            
            if(response == 'y'){//wantToPlaySmth
                int choice = -1;
                while (choice < 0 || choice >= idx)
                {
                    std::string str;
                    std::cout<<"Choose card to play : ";
                    std::cin>>str;
                    try {
                        choice = std::stoi(str);
                    }
                    catch (const std::exception & e) {
                        std::cout << "Invalid argument : " << str << std::endl;
                    }
                }
                if(choice < (!action.hasPlayedLand? hand->getLands().size() : 0 )){
                    auto card = std::move(playerToPlay->getHand()->summonLand(choice));
                    playerToPlay->getBattlefield()->add(std::move(card));
                    action.hasPlayedLand = true;
                }else
                if(choice < (!action.hasPlayedLand? hand->getLands().size() : 0 ) + hand->getCreatures().size()){
                    auto card = std::move(playerToPlay->getHand()->summonCreature(choice - (!action.hasPlayedLand? hand->getLands().size() : 0 )));
                    stack.get()->add(std::move(card));
                }else
                if(choice < (!action.hasPlayedLand? hand->getLands().size() : 0 ) + hand->getCreatures().size() + hand->getEnchantements().size()){
                    auto card = std::move(playerToPlay->getHand()->summonEnchantement(choice - (!action.hasPlayedLand? hand->getLands().size() : 0 ) - hand->getCreatures().size()));
                    stack.get()->add(std::move(card));
                }else
                if(choice < (!action.hasPlayedLand? hand->getLands().size() : 0 ) + hand->getCreatures().size() + hand->getEnchantements().size() + hand->getInstants().size()){
                    auto card = std::move(playerToPlay->getHand()->summonInstant(choice - (!action.hasPlayedLand? hand->getLands().size() : 0 ) - hand->getCreatures().size() - hand->getEnchantements().size()));
                    stack.get()->add(std::move(card));
                }else
                if(choice < (!action.hasPlayedLand? hand->getLands().size() : 0 ) + hand->getCreatures().size() + hand->getEnchantements().size() + hand->getInstants().size() + hand->getSorceries().size()){
                    auto card = std::move(playerToPlay->getHand()->summonSorcery(choice - (!action.hasPlayedLand? hand->getLands().size() : 0 ) - hand->getCreatures().size() - hand->getEnchantements().size() - hand->getInstants().size()));
                    stack.get()->add(std::move(card));
                }

                if(stack->getLength() > 0)//If it's a land, nothing will be on the stack
                    while(opponent->castSpellOrAbility() || playerToPlay->castSpellOrAbility());
                stack.get()->solve();
            }else{
                action.nextPhase();
            }
        };

        break;

    
    /* COMBAT PHASE */
    case Phase::BEGINNING_OF_COMBAT_STEP:
        std::cout<<"Beginning of Combat Step"<<std::endl;
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;

    case Phase::DECLARE_ATTACKER_STEP:
        std::cout<<"Declare Attacker Step"<<std::endl;
        playerToPlay->setAttackingCards();
        if(playerToPlay->getAttackingCards().size() > 0)
            while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;
    case Phase::DECLARE_BLOCKER_STEP:
        std::cout<<"Declare Blocker Step"<<std::endl;
        opponent->setBlockingCards(playerToPlay->getAttackingCards());
        if(playerToPlay->getAttackingCards().size() > 0)
            while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;

    
    case Phase::COMBAT_DAMAGE_STEP:
        std::cout<<"Combat Damage Step"<<std::endl;
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
        std::cout<<"End of Combat Step"<<std::endl;
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;

    /* SECOND MAIN PHASE */
    case Phase::SECOND_MAIN_PHASE:
        std::cout<<"Second Main Phase"<<std::endl;
        if(true){//wantToPlaySmth
            //playerToPlay->summonCard(0);//TODO choose card to play
            if(stack->getLength()>0)//If it's a land, nothing will be on the stack
                while(opponent->castSpellOrAbility() || playerToPlay->castSpellOrAbility());
            stack.get()->solve();
        }else{
        }
        
        break;

    /* ENDING PHASE */
    case Phase::END_STEP:
        std::cout<<"End Step"<<std::endl;
        while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
        stack->solve();

        break;
    
    case Phase::CLEANUP_STEP:
        std::cout<<"Cleanup Step"<<std::endl;
        while(playerToPlay->getHand()->getLength() > 7) {
            Card* chosenOne;
            playerToPlay->killCard(chosenOne);
        }

        break;

    default:
        //! ERROR
        break;
    }

}

void Game::resolveEvent(Event event) {
    for(uint8_t i = 0; playerToPlay->getBattlefield()->getLength(); i += 1) {
        Creature* card =  dynamic_cast<Creature*> (playerToPlay->getBattlefield()->getCard(i));
        if(card) {
            std::vector<std::function<void(Event)> > abilities = card->getTriggerAbilities();
            for(uint8_t j = 0; j < abilities.size(); j += 1) {
                abilities.at(i)(event); //TODO abilities affect game
            }
        }
    }
}

void Game::chooseCards() {
    auto& maker = CardMaker::getInst();
    while(player1.getLibrary()->getLength() < 60) {

        auto newCard = std::move(maker.create(0));
        std::cout<<"Player 1 - ";
        player1.getLibrary()->add(std::move(newCard));
        
        // std::unique_ptr<Card> newCard = nullptr;
        // while(newCard == nullptr) {
        //     std::string str;
        //     std::cout<<"Enter card id to add : ";
        //     std::cin>>str;
        //     int id;
        //     try {
        //         id = std::stoi(str);
        //         newCard = std::move(maker.create((uint8_t)id));
        //     }
        //     catch (const std::exception & e) {
        //         std::cout << "Invalid argument : " << str << std::endl;
        //     }
            
        // } 
        // auto cards = player1.getLibrary()->getCards();
        // int freq = std::count_if(cards.begin(), cards.end(),
        //     [&](Card* i) {
        //         return (i->getCardId() == newCard.get()->getCardId());
        //     });
        
        // if(freq >= 4 && Deck::getCardType(newCard.get()) != CardType::LAND) {
        //     std::cout<< "Error - already 4 occurence of this card in your deck"<<std::endl;
        // }else {
        //     std::cout<<"Added " <<newCard.get()->getName()<< " to player 1"<<std::endl;
        //     player1.getLibrary()->add(std::move(newCard));
        // }

    }
    while(player2.getLibrary()->getLength() < 60) {
        auto newCard = std::move(maker.create(0));
        std::cout<<"Player 2 - ";
        player2.getLibrary()->add(std::move(newCard));
        
        // std::unique_ptr<Card> newCard = nullptr;
        // while(newCard == nullptr) {
        //     std::string str;
        //     std::cout<<"Enter card id to add : ";
        //     std::cin>>str;
        //     int id;
        //     try {
        //         id = std::stoi(str);
        //         newCard = std::move(maker.create((uint8_t)id));
        //     }
        //     catch (const std::exception & e) {
        //         std::cout << "Invalid argument : " << str << std::endl;
        //     }
            
        // } 
        // auto cards = player2.getLibrary()->getCards();
        // int freq = std::count_if(cards.begin(), cards.end(),
        //     [&](Card* i) {
        //         return (i->getCardId() == newCard.get()->getCardId());
        //     });
        
        // if(freq >= 4 && Deck::getCardType(newCard.get()) != CardType::LAND) {
        //     std::cout<< "Error - already 4 occurence of this card in your deck"<<std::endl;
        // }else {
        //     std::cout<<"Added " <<newCard.get()->getName()<< " to player 2"<<std::endl;
        //     player2.getLibrary()->add(std::move(newCard));
        // }

    }
}

void Game::initGame() {
    player1.getLibrary()->shuffle();
    player2.getLibrary()->shuffle();
    for(int i = 0; i < 7; i += 1) {
        std::cout<<"Player 1 - ";
        player1.draw();
        std::cout<<"Player 2 - ";
        player2.draw();
    }
}