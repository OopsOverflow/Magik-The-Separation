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
        std::cout<<player1.getName()<<" - ";
        player1.draw();
        std::cout<<player2.getName()<<" - ";
        player2.draw();
    }
}

#include <random>
void Game::chooseCards() {
    auto& maker = CardMaker::getInst();
    while(player1.getLibrary()->getLength() < 60) {

        std::random_device r;
    
        // Choose a random mean between 1 and 6
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(0, 20);
        int mean = uniform_dist(e1);
        auto newCard = std::move(maker.create((uint16_t)mean));
        std::cout<<player1.getName()<<" - ";
        player1.getLibrary()->add(std::move(newCard));
        
        // std::unique_ptr<Card> newCard = nullptr;
        // while(newCard == nullptr) {
        //     std::string str;
        //     std::cout<<"Enter card id to add : ";
        //     std::cin>>str;
        //     int id;
        //     try {
        //         id = std::stoi(str);
        //         newCard = std::move(maker.create((uint16_t)id));
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

        std::random_device r;
    
        // Choose a random mean between 1 and 6
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(0, 20);
        int mean = uniform_dist(e1);
        auto newCard = std::move(maker.create((uint16_t)mean));
        std::cout<<player2.getName()<<" - ";
        player2.getLibrary()->add(std::move(newCard));
        
        // std::unique_ptr<Card> newCard = nullptr;
        // while(newCard == nullptr) {
        //     std::string str;
        //     std::cout<<"Enter card id to add : ";
        //     std::cin>>str;
        //     int id;
        //     try {
        //         id = std::stoi(str);
        //         newCard = std::move(maker.create((uint16_t)id));
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


bool Game::castInstantsOrAbilities(Player* castingPlayer, bool lastHasPlayed) {
        bool hasCasted = false;
        if(castingPlayer->getHand()->getLength() > 0) {
            
            auto playables = playerToPlay->getCastableInstantsOrAbilities();
            if(playables.size() > 0) {
                std::cout<<castingPlayer->getName()<<std::endl;
                std::cout<<"Playable cards : "<< playables.size() << std::endl;
                for(size_t i = 0; i < playables.size(); i += 1) { 
                    std::cout<<i<<" - "<<castingPlayer->seekCard(playables.at(i))->getName()<<std::endl;
                }
            }

            char response = 0;//TODO autoscrool at this point
            while (response != 'y' && response != 'n' && playables.size() > 0)
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
            
            if(response == 'y' && playables.size() > 0) {//wantToPlaySmth
                size_t choice = playables.size();
                while (choice < 0 || choice >= playables.size())
                {
                    std::string str;
                    std::cout<<"Choose card to play : ";
                    std::cin>>str;
                    try {
                        choice = std::stoi(str);
                    }
                    catch (const std::exception &_) {
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
        if(action.somethingPlayed) {
            castInstantsOrAbilities(playerToPlay);
            solveStack();
            action.somethingPlayed = false;
        }
        
        action.nextPhase();
        break;

    case Phase::DRAW_STEP:
        std::cout<<"///Draw Step///"<<std::endl<<std::endl;

       //Player must draw a card from his library        
        playerToPlay->draw();
        castInstantsOrAbilities(playerToPlay);
        solveStack();
        action.somethingPlayed = false;
        
        action.nextPhase();
        break;


    /* FIRST MAIN PHASE */  
    case Phase::FIRST_MAIN_PHASE:
        std::cout<<"///First Main Phase///"<<std::endl<<std::endl;
        {    

            std::cout<<playerToPlay->getName()<<std::endl;
 
            auto playables = playerToPlay->getPlayableCards(action.hasPlayedLand);
            std::cout<<"Playable cards : "<< playables.size() << std::endl;
            for(size_t i = 0; i < playables.size(); i += 1) { 
                std::cout<<"    "<<i<<" - "<<playerToPlay->seekCard(playables.at(i))->getColorStr()<<playerToPlay->seekCard(playables.at(i))->getName()<<std::endl;
            }

            //You can cast any number of sorceries, instants, creatures, artifacts, enchantments, and planeswalkers, and you can activate abilities
            char response = 0;
            while (response != 'y' && response != 'n' && playables.size() > 0)
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
            
            if(response == 'y' && playables.size() > 0) {//wantToPlaySmth
                size_t choice = playables.size();
                while (choice < 0 || choice >= playables.size())
                {
                    std::string str;
                    std::cout<<"Choose card to play : ";
                    std::cin>>str;
                    try {
                        choice = std::stoi(str);
                    }
                    catch (const std::exception &_) {
                        std::cout << "Invalid argument : " << str << std::endl;
                    }
                }
                std::unique_ptr<Card> playedCard = playerToPlay->playCard(playables.at(choice));
                std::cout<<"Played "<<playedCard.get()->getName()<<std::endl;
                Land* landCard = dynamic_cast<Land*>(playedCard.get());
                if(landCard != nullptr) { //is a land
                    playerToPlay->getBattlefield()->add(std::move(playedCard));
                    action.hasPlayedLand = true;
                    action.somethingPlayed = true;
                }else {
                    playerToPlay->getBattlefield()->tapColors(playedCard.get()->getCost());
                    stack->add({std::move(playedCard), playerToPlay});
                    castInstantsOrAbilities(opponent);
                    solveStack();
                    action.somethingPlayed = false;
                }
            
            }else{
                action.nextPhase();
            }
        };

        break;

    
    /* COMBAT PHASE */
    case Phase::BEGINNING_OF_COMBAT_STEP:
        std::cout<<"Beginning of Combat Step"<<std::endl<<std::endl;
        if(action.somethingPlayed) {
            castInstantsOrAbilities(playerToPlay);
            solveStack();
            action.somethingPlayed = false;
        }
        action.nextPhase();
        break;

    case Phase::DECLARE_ATTACKER_STEP:
        std::cout<<"Declare Attacker Step"<<std::endl<<std::endl;
        playerToPlay->getBattlefield()->setAttackingCreatures();
        castInstantsOrAbilities(playerToPlay);
        solveStack();
        action.somethingPlayed = false;
        action.nextPhase();
        break;


    case Phase::DECLARE_BLOCKER_STEP:
        std::cout<<"Declare Blocker Step"<<std::endl<<std::endl;
        {
            if(playerToPlay->getBattlefield()->getAttackingCreatures().size() > 0) {
                std::vector<Creature*> attacking;
                for(auto creature : playerToPlay->getBattlefield()->getAttackingCreatures()) {
                    attacking.push_back(dynamic_cast<Creature*>(playerToPlay->seekCard(creature)));//Relatively safe as uuid comes from attacking creatures
                }
            
                opponent->getBattlefield()->setBlockingCreatures(attacking);
                castInstantsOrAbilities(playerToPlay);
                solveStack();
                action.somethingPlayed = false;
            }
        }
        
        action.nextPhase();
        break;

    
    case Phase::COMBAT_DAMAGE_STEP:
        {
            std::cout<<"Combat Damage Step"<<std::endl<<std::endl;
            auto attacking = playerToPlay->getBattlefield()->getAttackingCreatures();
            auto blocking = opponent->getBattlefield()->getBlockingCreatures();
            for(size_t i = 0; i < attacking.size(); i += 1) {
                Creature* attackingCard = dynamic_cast<Creature*> (playerToPlay->seekCard(attacking.at(i)));
                if(blocking.at(i).size() > 0) {
                    for(size_t j = 0; j < opponent->getBattlefield()->getBlockingCreatures().at(i).size(); j += 1) {
                        Creature* blockingCard = dynamic_cast<Creature*> (opponent->seekCard(blocking.at(i).at(j)));
                        blockingCard->block(attackingCard);
                        if(attackingCard->hasStaticAbility(StaticAbility::TRAMPLE) &&
                            j == opponent->getBattlefield()->getBlockingCreatures().at(i).size() - 1 &&
                            attackingCard->getTmpStats().second > 0) {
                            opponent->takeDamage(attackingCard->getTmpStats().first);
                            if(attackingCard->hasStaticAbility(StaticAbility::LIFELINK))
                                playerToPlay->heal(attackingCard->getTmpStats().first);
                           }

                    }
                }else{
                    opponent->takeDamage(attackingCard->getTmpStats().first);
                    if(attackingCard->hasStaticAbility(StaticAbility::LIFELINK))
                        playerToPlay->heal(attackingCard->getTmpStats().first);
                }
            }

            for(size_t i = 0; i < attacking.size(); i += 1) {
                Creature* attackingCard = dynamic_cast<Creature*> (playerToPlay->seekCard(attacking.at(i)));
                    if(attackingCard->getTmpStats().second <= 0) playerToPlay->killCard(attacking.at(i));
            }
            for(size_t i = 0; i < attacking.size(); i += 1) {
                for(size_t j = 0; j < blocking.at(i).size(); j += 1) {
                    Creature* blockingCard = dynamic_cast<Creature*> (opponent->seekCard(blocking.at(i).at(j)));
                        if(blockingCard->getTmpStats().second <= 0) opponent->killCard(blocking.at(i).at(j));
                }
            }

        }
        if(playerToPlay->getBattlefield()->getAttackingCreatures().size() > 0) {
            castInstantsOrAbilities(playerToPlay);
            solveStack();
            action.somethingPlayed = false;
        }
        action.nextPhase();
        break;
    case Phase::END_OF_COMBAT_STEP:
        std::cout<<"End of Combat Step"<<std::endl<<std::endl;
        if(action.somethingPlayed) {
            castInstantsOrAbilities(playerToPlay);
            solveStack();
            action.somethingPlayed = false;
        }
        action.nextPhase();
        break;

    /* SECOND MAIN PHASE */
    case Phase::SECOND_MAIN_PHASE:
        std::cout<<"Second Main Phase"<<std::endl<<std::endl;
        {    

            std::cout<<playerToPlay->getName()<<std::endl;
 
            auto playables = playerToPlay->getPlayableCards(action.hasPlayedLand);
            std::cout<<"Playable cards : "<< playables.size() << std::endl;
            for(size_t i = 0; i < playables.size(); i += 1) { 
                std::cout<<"    "<<i<<" - "<<playerToPlay->seekCard(playables.at(i))->getColorStr()<<playerToPlay->seekCard(playables.at(i))->getName()<<std::endl;
            }

            //You can cast any number of sorceries, instants, creatures, artifacts, enchantments, and planeswalkers, and you can activate abilities
            char response = 0;
            while (response != 'y' && response != 'n' && playables.size() > 0)
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
            
            if(response == 'y' && playables.size() > 0) {//wantToPlaySmth
                size_t choice = playables.size();
                while (choice < 0 || choice >= playables.size())
                {
                    std::string str;
                    std::cout<<"Choose card to play : ";
                    std::cin>>str;
                    try {
                        choice = std::stoi(str);
                    }
                    catch (const std::exception &_) {
                        std::cout << "Invalid argument : " << str << std::endl;
                    }
                }
                std::unique_ptr<Card> playedCard = playerToPlay->playCard(playables.at(choice));
                std::cout<<"Played "<<playedCard.get()->getName()<<std::endl;
                Land* landCard = dynamic_cast<Land*>(playedCard.get());
                if(landCard != nullptr) { //is a land
                    playerToPlay->getBattlefield()->add(std::move(playedCard));
                    action.hasPlayedLand = true;
                    action.somethingPlayed = true;
                }else {
                    playerToPlay->getBattlefield()->tapColors(playedCard.get()->getCost());
                    stack->add({std::move(playedCard), playerToPlay});
                    castInstantsOrAbilities(opponent);
                    solveStack();
                    action.somethingPlayed = false;
                }
            
            }else{
                action.nextPhase();
            }
        };
        break;

    /* ENDING PHASE */
    case Phase::END_STEP:
        std::cout<<"End Step"<<std::endl<<std::endl;
        if(action.somethingPlayed) {
            castInstantsOrAbilities(playerToPlay);
            solveStack();
            action.somethingPlayed = false;
        }
        action.nextPhase();
        break;
    
    case Phase::CLEANUP_STEP:
        std::cout<<"Cleanup Step"<<std::endl<<std::endl;
        while(playerToPlay->getHand()->getLength() > 7) {
            std::cout<<"You have to throw cards : " << playerToPlay->getHand()->getLength() - 7<<std::endl;
            std::vector<uint16_t> cardsId;
            int idx = 0;
            for(size_t i = 0; i < playerToPlay->getHand()->getCreatures().size(); i +=1) {
                cardsId.push_back(playerToPlay->getHand()->getCreatures().at(i)->getCardUuid());
                std::cout<<"    "<<idx++<<" - "<<playerToPlay->getHand()->getCreatures().at(i)->getName()<<std::endl;
            }
            for(size_t i = 0; i < playerToPlay->getHand()->getLands().size(); i +=1) {
                cardsId.push_back(playerToPlay->getHand()->getLands().at(i)->getCardUuid());
                std::cout<<"    "<<idx++<<" - "<<playerToPlay->getHand()->getLands().at(i)->getName()<<std::endl;
            }
            for(size_t i = 0; i < playerToPlay->getHand()->getInstants().size(); i +=1) {
                cardsId.push_back(playerToPlay->getHand()->getInstants().at(i)->getCardUuid());
                std::cout<<"    "<<idx++<<" - "<<playerToPlay->getHand()->getInstants().at(i)->getName()<<std::endl;
            }
            for(size_t i = 0; i < playerToPlay->getHand()->getEnchantements().size(); i +=1) {
                cardsId.push_back(playerToPlay->getHand()->getEnchantements().at(i)->getCardUuid());
                std::cout<<"    "<<idx++<<" - "<<playerToPlay->getHand()->getEnchantements().at(i)->getName()<<std::endl;
            }
            for(size_t i = 0; i < playerToPlay->getHand()->getSorceries().size(); i +=1) {
                cardsId.push_back(playerToPlay->getHand()->getSorceries().at(i)->getCardUuid());
                std::cout<<"    "<<idx++<<" - "<<playerToPlay->getHand()->getSorceries().at(i)->getName()<<std::endl;
            }
            int choice = -1;
            while (choice < 0 || choice >= (int)cardsId.size())
            {
                std::string str;
                std::cout<<"Choose card to throw : ";
                std::cin>>str;
                try {
                    choice = std::stoi(str);
                }
                catch (const std::exception &_) {
                    std::cout << "Invalid argument : " << str << std::endl;
                }
            }
            playerToPlay->killCard(cardsId.at(choice));

        }
        action.nextPhase();
        break;

    default:
        action.nextPhase();
        break;
    }

}

Player *Game::getPlayer1() {
    return &player1;
}

Player *Game::getPlayer2() {
    return &player2;
}
