//
// Created by houssem on 04/01/2022.
//

#include "Battlefield.h"


Battlefield::Battlefield() : Deck() {
}

Battlefield::~Battlefield() {

}

std::unique_ptr<Card> Battlefield::popCard(uint8_t cardId) {
    for(size_t i = 0; i < creatures.size(); i += 1) {
        if(creatures.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(creatures.at(i));
            creatures.erase(creatures.begin() + i);
            return ptr;
        }

        for(size_t j = 0; i<creatures.at(i)->getAttachedCards().size(); j += 1) {
            if(creatures.at(i).get()->getAttachedCards().at(j)->getCardId() == cardId) {
                std::unique_ptr<Card> ptr(creatures.at(i)->getAttachedCards().at(j));        //TODO Wip DO NOT WORK
                creatures.at(i)->getAttachedCards().erase(creatures.at(i)->getAttachedCards().begin() + i);
            return ptr;
            }

        }
    }
        
    for(size_t i = 0; i < lands.size(); i += 1) {
        if(lands.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(lands.at(cardId));
            lands.erase(lands.begin() + i);
            return ptr;
        }
    }

    std::cout<< "Error - no card was found in Battlefield"<< std::endl;
    return nullptr;  
}

Card* Battlefield::getCard(uint8_t cardId) {
    for(auto const& card : creatures)
        if(card.get()->getCardId() == cardId) return card.get(); //TODO add enchants
    for(auto const& card : lands)
        if(card.get()->getCardId() == cardId) return card.get();
    
    std::cout<< "Error - no card was found in Battlefield"<< std::endl;
    return nullptr;
}

uint8_t Battlefield::getLength() const {
    return (uint8_t)(creatures.size() + lands.size());
}

void Battlefield::add(std::unique_ptr<Card> card) {
    Card* cardToAdd = card.get();
    CardType type = getCardType(cardToAdd);
    switch (type)
    {
    case (CardType::CREATURE):
        {
            Creature *tmp = dynamic_cast<Creature*>(card.get());
            std::unique_ptr<Creature> creature;
            if(tmp != nullptr)
            {
                card.release();
                creature.reset(tmp);
                creatures.push_back(std::move(creature));

            }else {
                std::runtime_error("Error - cast into creature in Hand");  
            }
        }
        break;

    case (CardType::LAND):
        {
            Land *tmp = dynamic_cast<Land*>(card.get());
            std::unique_ptr<Land> land;
            if(tmp != nullptr)
            {
                card.release();
                land.reset(tmp);
                lands.push_back(std::move(land));

            }else {
                std::runtime_error("Error - cast into land in Hand");  
            }
        }
        break;

    default:
        std::runtime_error("Error - cannot find cast in Hand");
        break;
    }
}

std::vector<Creature*> Battlefield::getCreatures() {
    std::vector<Creature*> result;
    for(auto& card : creatures)
        result.push_back(card.get());
    return result;
}

std::vector<Land*> Battlefield::getLands() {
    std::vector<Land*> result;
    for(size_t i = 0; i < lands.size(); i += 1)
        result.push_back(lands.at(i).get());
    return result;
}


void Battlefield::setAttackingCreatures() {
    attackingCreatures.clear();
    std::vector<uint8_t> playables;
    for(auto creature : getCreatures())
        if(!creature->isTapped()) 
            playables.push_back(creature->getCardUuid());

    //TODO can be optimised but don't need to (graphic)
    std::cout<<"Playable creatures : "<<std::endl;
    for(size_t i = 0; i < playables.size(); i += 1)
        std::cout << i << " - " << getCard(playables.at(i))->getName() << std::endl;    

    char response = 0;//TODO autoscrool at this point
    while (response != 'y' && response != 'n' && playables.size() > 0)
    {

        std::cout<<"Do you want to attack with something ? (y/n) ";
        std::string str;
        std::cin>>str;
        response = str[0];
        if(response == 'y' && playables.size() == 0) {
            std::cout<<"You can't play anything this turn, you should say \"no\""<<std::endl;
            response = 0;
        }
    }
    if(response == 'y') {
        std::vector<uint8_t> cardsIdx;
        while (cardsIdx.size() < playables.size() && response == 'y')
        {
            int choice = -1;
            while (choice < 0 || choice >= (int)playables.size())
            {
                std::string str;
                std::cout<<"Choose card to play : ";
                std::cin>>str;
                try {
                    choice = std::stoi(str);
                    if(std::find(cardsIdx.begin(), cardsIdx.end(), choice) != cardsIdx.end()) {
                        std::cout<<"You already attack with this card"<<std::endl;
                        choice = -1;
                    }
                        
                }
                catch (const std::exception & e) {
                    std::cout << "Invalid argument : " << str << std::endl;
                }
            }
            
            cardsIdx.push_back((uint8_t)choice);
            response = 0;
            while (response != 'y' && response != 'n' && cardsIdx.size() < playables.size())
            {
                std::cout<<"Do you want to attack with another card ? (y/n) ";
                std::string str;
                std::cin>>str;
                response = str[0];
            }

        }
        for(auto card : cardsIdx)
            attackingCreatures.push_back(playables.at(card));
        
    }
}

std::vector<uint8_t> Battlefield::getAttackingCreatures() {
    
    return attackingCreatures;
}


void Battlefield::setBlockingCreatures(std::vector<Creature *> attacking) {
    blockingCreatures.clear();
    std::vector<uint8_t> playables;
    for(auto creature : getCreatures())
        if(!creature->isTapped()) 
            playables.push_back(creature->getCardUuid());
    
    std::cout<<"Attacking creatures : "<<std::endl;
    for(size_t i = 0; i < attacking.size(); i += 1)
        std::cout<<i<<" - "<<attacking.at(i)->getName()<<std::endl;

    char response = 0;//TODO autoscrool at this point
    while (response != 'y' && response != 'n' && playables.size() > 0)
    {

        std::cout<<"Do you want to block something ? (y/n) ";
        std::string str;
        std::cin>>str;
        response = str[0];
        if(response == 'y' && playables.size() == 0) {
            std::cout<<"You can't play anything this turn, you should say \"no\""<<std::endl;
            response = 0;
        }
    }

    if(response == 'y') {
        std::vector<uint8_t> cardsIdx;
        while (cardsIdx.size() < playables.size() && response == 'y')
        {
            int choice = -1;
            while (choice < 0 || choice >= (int)playables.size())
            {
                std::string str;
                std::cout<<"Choose card to play : ";
                std::cin>>str;
                try {
                    choice = std::stoi(str);
                    if(std::find(cardsIdx.begin(), cardsIdx.end(), choice) != cardsIdx.end()) {
                        std::cout<<"You already attack with this card"<<std::endl;
                        choice = -1;
                    }
                        
                }
                catch (const std::exception & e) {
                    std::cout << "Invalid argument : " << str << std::endl;
                }
            }
            
            cardsIdx.push_back((uint8_t)choice);
            response = 0;
            while (response != 'y' && response != 'n' && cardsIdx.size() < playables.size())
            {
                std::cout<<"Do you want to attack with another card ? (y/n) ";
                std::string str;
                std::cin>>str;
                response = str[0];
            }

        }
        for(auto card : cardsIdx)
            attackingCreatures.push_back(playables.at(card));
        
    }


}

std::vector<std::vector<uint8_t> > Battlefield::getBlockingCreatures() {
    return blockingCreatures;
}

void Battlefield::tapColors(std::map<Color, int> cost) {
    for(auto colorCost : cost) {
        if(colorCost.first != Color::WBBRG) {
            for(int j = 0; j < colorCost.second; j += 1) {
                auto it = std::find_if(lands.begin(), lands.end(), [&](const auto& x) { return !x->isTapped() && colorCost.first == x->getColor();});
                (*it)->tap();
            }
        }else {
            //TODO Choose card to tap

        }
    }

}