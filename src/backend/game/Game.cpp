//
// Created by pierre on 13/01/2022.
//

#include "Game.h"
#include "../components/card/CardMaker.h"

#include <algorithm>

Game::Game() : stack(new Stack()), player1("Bob"), player2("Henri"), playerToPlay(&player1), opponent(&player2) {
    std::cout<<"Game instance created"<<std::endl;
}

Game::~Game() {

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

void Game::chooseCards() {
    auto& maker = CardMaker::getInst();
    while(player1.getLibrary()->getLength() < 60) {

        auto newCard = std::move(maker.create(0));
        auto newPlain = std::move(maker.create(1));
        std::cout<<"Player 1 - ";
        player1.getLibrary()->add(std::move(newCard));
        player1.getLibrary()->add(std::move(newPlain));
        
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
        auto newPlain = std::move(maker.create(1));
        std::cout<<"Player 2 - ";
        player2.getLibrary()->add(std::move(newCard));
        player2.getLibrary()->add(std::move(newPlain));
        
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


// void Game::resolveEvent(Event event) {
//     for(uint8_t i = 0; playerToPlay->getBattlefield()->getLength(); i += 1) {
//         Creature* card =  dynamic_cast<Creature*> (playerToPlay->getBattlefield()->getCard(i));
//         if(card) {
//             std::vector<std::function<void(Event)> > abilities = card->getTriggerAbilities();
//             for(uint8_t j = 0; j < abilities.size(); j += 1) {
//                 abilities.at(i)(event); //TODO abilities affect game
//             }
//         }
//     }
// }

bool Game::castInstantsOrAbilities(Player* castingPlayer, bool lastHasPlayed) {
        bool hasCasted = false;
        if(castingPlayer->getHand()->getLength() > 0) {
            std::cout<<castingPlayer->getName()<<std::endl;
            auto playables = playerToPlay->getCastableInstantsOrAbilities();
            std::cout<<"Playable cards : "<< playables.size() << std::endl;
            for(size_t i = 0; i < playables.size(); i += 1) { 
                std::cout<<i<<" - "<<castingPlayer->seekCard(playables.at(i))->getName()<<std::endl;
            }

            char response = 0;//TODO autoscrool at this point
            while (response != 'y' && response != 'n')
            {

                std::cout<<"Do you want to play something ? (y/n) ";
                std::string str;
                std::cin>>str;
                response = str[0];
                if(response == 'y' && playables.size() == 0) {
                    std::cout<<"You can't play anything this turn, you should say \"no\""<<std::endl;
                    response = 0;
                }
                    
            }
            
            if(response == 'y' && playables.size() != 0) {//wantToPlaySmth
                size_t choice = playables.size();
                while (choice < 0 || choice >= playables.size())
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
                //TODO add abilities
                auto newCard = std::move(castingPlayer->getHand()->popCard(playables.at(choice)));
                castingPlayer->getBattlefield()->tapColors(newCard.get()->getCost());
                stack->add({std::move(newCard), castingPlayer});
                hasCasted = true;
            }

        }

        Player* nextCast = &player2;
        if(castingPlayer == &player2) nextCast = &player1;
        if(hasCasted || lastHasPlayed) castInstantsOrAbilities(nextCast, hasCasted);

        return false;
}

void Game::solveStack() {
    while(stack->getLength() > 0) {
        std::pair<std::unique_ptr<Card>, Player *> pair = stack->getTopPair();
        if(dynamic_cast<Creature*>(pair.first.get()) != nullptr) {
            pair.second->getBattlefield()->add(std::move(pair.first));
        }else{
            std::runtime_error("Couldn't pop card from stack");
        }
        
    }
}



void Game::solvePhase() {
    GameAction& action = GameAction::getInst();
    switch (action.getPhase())
    {
    /* BEGINNING PHASE */
    case Phase::UNTAP_STEP:
        std::cout<<"///Untap Step///"<<std::endl<<std::endl;
        //Choose player to play
        if(action.getTurn() % 2 == 1) {
            playerToPlay = &player1;
            opponent = &player2;
        }else{
            playerToPlay = &player2;
            opponent = &player1;
        }
        action.hasPlayedLand = false;

        //You untap all your tapped permanents
        playerToPlay->unTapAll();
        
        action.nextPhase();
        break;

    case Phase::UPKEEP_STEP:
        std::cout<<"///Upkeep Step///"<<std::endl<<std::endl;
        //TODO trigger beginnig of unkeep step

        //Players can cast instants and activate abilities

        castInstantsOrAbilities(playerToPlay);
        solveStack();
        
        action.nextPhase();
        break;

    case Phase::DRAW_STEP:
        std::cout<<"///Draw Step///"<<std::endl<<std::endl;

       //Player must draw a card from his library        
        playerToPlay->draw();
        castInstantsOrAbilities(playerToPlay);
        solveStack();
        
        action.nextPhase();
        break;


    /* FIRST MAIN PHASE */  
    case Phase::FIRST_MAIN_PHASE:
        std::cout<<"///First Main Phase///"<<std::endl<<std::endl;
        {    
            
            if(playerToPlay == &player1)
                std::cout<<"Player 1 "<<std::endl;
            else
                std::cout<<"Player 2 "<<std::endl;

            auto playables = playerToPlay->getPlayableCards(action.hasPlayedLand);
            std::cout<<"Playable cards : "<< playables.size() << std::endl;
            for(size_t i = 0; i < playables.size(); i += 1) { 
                std::cout<<i<<" - "<<playerToPlay->seekCard(playables.at(i))->getName()<<std::endl;
            }

            //You can cast any number of sorceries, instants, creatures, artifacts, enchantments, and planeswalkers, and you can activate abilities
            char response = 0;//TODO autoscrool at this point
            while (response != 'y' && response != 'n')
            {

                std::cout<<"Do you want to play something ? (y/n) ";
                std::string str;
                std::cin>>str;
                response = str[0];
                if(response == 'y' && playables.size() == 0) {
                    std::cout<<"You can't play anything this turn, you should say \"no\""<<std::endl;
                    response = 0;
                }
                    
            }
            
            if(response == 'y' && playables.size() != 0) {//wantToPlaySmth
                size_t choice = playables.size();
                while (choice < 0 || choice >= playables.size())
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
                std::unique_ptr<Card> playedCard = playerToPlay->playCard(playables.at(choice));
                std::cout<<"Played "<<playedCard.get()->getName()<<std::endl;
                Land* landCard = dynamic_cast<Land*>(playedCard.get());
                if(landCard != nullptr) { //is a land
                    playerToPlay->getBattlefield()->add(std::move(playedCard));
                    action.hasPlayedLand = true;
                }else {
                    playerToPlay->getBattlefield()->tapColors(playedCard.get()->getCost());
                    stack->add({std::move(playedCard), playerToPlay});
                    castInstantsOrAbilities(opponent);
                    solveStack();
                }
            
            }else{
                action.nextPhase();
            }
        };

        break;

    
    /* COMBAT PHASE */
    case Phase::BEGINNING_OF_COMBAT_STEP:
        castInstantsOrAbilities(playerToPlay);
        solveStack();
        action.nextPhase();

        break;

    case Phase::DECLARE_ATTACKER_STEP:
        std::cout<<"Declare Attacker Step"<<std::endl;
        playerToPlay->getBattlefield()->setAttackingCreatures();

        castInstantsOrAbilities(playerToPlay);
        solveStack();
        action.nextPhase();
        break;


    case Phase::DECLARE_BLOCKER_STEP:
        std::cout<<"Declare Blocker Step"<<std::endl;
        {
            std::vector<Creature*> attacking;
            for(auto creature : playerToPlay->getBattlefield()->getAttackingCreatures())
                attacking.push_back(dynamic_cast<Creature*>(playerToPlay->seekCard(creature)));
            opponent->getBattlefield()->setBlockingCreatures(attacking);
        }
        
//if(playerToPlay->getBattlefield().getAttackingCards().size() > 0)
        castInstantsOrAbilities(playerToPlay);
        solveStack();
        
        action.nextPhase();
        break;

    
    case Phase::COMBAT_DAMAGE_STEP:
        // std::cout<<"Combat Damage Step"<<std::endl;
        // for(size_t i = 0; i < playerToPlay->getAttackingCards().size(); i += 1) {
        //     if(opponent->getBlockingCards().at(i).size() > 0) {

        //         for(size_t j = 0; i < opponent->getBlockingCards().at(i).size(); j += 1) {

        //             if(playerToPlay->getAttackingCards().at(i)->getTempThougness() > 0) {

        //                 opponent->getBlockingCards().at(i).at(j)->block(playerToPlay->getAttackingCards().at(i));
        //                 if(opponent->getBlockingCards().at(i).at(j)->getTempThougness() <= 0) {
        //                     opponent->killCard(opponent->getBlockingCards().at(i).at(j));
        //                 }
        //             }
        //         }
        //     }else{
        //         opponent->takeDamage(playerToPlay->getAttackingCards().at(i)->getPower());
        //     }
        // }
// while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
// stack->solve();
        action.nextPhase();
        break;
    case Phase::END_OF_COMBAT_STEP:
        std::cout<<"End of Combat Step"<<std::endl;
// while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
// stack->solve();
        action.nextPhase();
        break;

    /* SECOND MAIN PHASE */
    case Phase::SECOND_MAIN_PHASE:
        std::cout<<"Second Main Phase"<<std::endl;
        if(true){//wantToPlaySmth
            //playerToPlay->summonCard(0);//TODO choose card to play
// if(stack->getLength()>0)//If it's a land, nothing will be on the stack
//     while(opponent->castSpellOrAbility() || playerToPlay->castSpellOrAbility());
// stack.get()->solve();
        }else{
        }
        action.nextPhase();
        break;

    /* ENDING PHASE */
    case Phase::END_STEP:
        std::cout<<"End Step"<<std::endl;
// while(playerToPlay->castSpellOrAbility() || opponent->castSpellOrAbility());
// stack->solve();
        action.nextPhase();
        break;
    
    case Phase::CLEANUP_STEP:
        std::cout<<"Cleanup Step"<<std::endl;
        while(playerToPlay->getHand()->getLength() > 7) {
        }
        action.nextPhase();
        break;

    default:
        action.nextPhase();
        break;
    }

}
