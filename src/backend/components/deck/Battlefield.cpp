//
// Created by houssem on 04/01/2022.
//

#include "Battlefield.h"
#include <algorithm>
#include <iterator>
#include <set>


Battlefield::Battlefield() : Deck() {
}

Battlefield::~Battlefield() = default;

std::unique_ptr<Card> Battlefield::popCard(uint16_t cardId) {
    for(size_t i = 0; i < creatures.size(); i += 1) {
        if(creatures.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(creatures.at(i));
            creatures.erase(creatures.begin() + i);
            
            auto it = std::find(attackingCreatures.begin(), attackingCreatures.end(), ptr->getCardUuid());
            if(it != attackingCreatures.end())attackingCreatures.erase(it);
            
            for(auto vec : blockingCreatures) {
                auto it2 = std::find(vec.begin(), vec.end(), ptr->getCardUuid());
                if(it2 != vec.end())vec.erase(it2);
            }

            return ptr;
        }

        for(size_t j = 0; j <creatures.at(i)->getAttachedCards().size(); j += 1) {
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

Card* Battlefield::seekCard(uint16_t cardId) {
    for(size_t i = 0; i < lands.size(); i += 1)
        if(lands.at(i)->getCardUuid() == cardId)
                return lands.at(i).get();


    for(size_t i = 0; i < creatures.size(); i += 1) {
        if(creatures.at(i)->getCardUuid() == cardId)
            return creatures.at(i).get();
        for(size_t j = 0; j < creatures.at(i)->getActivatedAbilities().size(); j += 1) {
            if(creatures.at(i)->getActivatedAbilities().at(j).getCardUuid() == cardId)
                return creatures.at(i).get();//TODO activatedAbilities
        }
        //TODO add enchants
    }
    
    std::cout<< "Error - no card was found in Battlefield"<< std::endl;
    return nullptr;
}

uint16_t Battlefield::getLength() const {
    return (uint16_t)(creatures.size() + lands.size());
}

std::string Battlefield::toJson() {
    std::string result;
    result += "{ \"lands\" : [";
    for(size_t i = 0; i < lands.size(); i += 1) {
        result += std::to_string(lands.at(i).get()->getCardUuid());
        if(i != lands.size()-1)result += ", ";
    }
    result += "], \"creatures\" : [";
    for(size_t i = 0; i < creatures.size(); i += 1) {
        result += std::to_string(creatures.at(i).get()->getCardUuid());
        if(i != creatures.size()-1)result += ", ";
    }
    result += "]}";
    return result;
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
    std::vector<uint16_t> playables;
    for(auto creature : getCreatures())
        if(!creature->isTapped() && !creature->isSummoned() && !creature->hasStaticAbility(StaticAbility::DEFENDER)) 
            playables.push_back(creature->getCardUuid());

    //TODO can be optimised but don't need to (graphic)
    std::cout<<"Playable creatures : "<<std::endl;
    for(size_t i = 0; i < playables.size(); i += 1)
        std::cout <<"   "<< i << " - " << seekCard(playables.at(i))->getName() << dynamic_cast<Creature*>(seekCard(playables.at(i)))->getTmpStats() << std::endl;    

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
        std::vector<uint16_t> cardsIdx;
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
                catch (const std::exception) {
                    std::cout << "Invalid argument : " << str << std::endl;
                }
            }
            
            cardsIdx.push_back((uint16_t)choice);
            response = 0;
            while (response != 'y' && response != 'n' && cardsIdx.size() < playables.size())
            {
                std::cout<<"Do you want to attack with another card ? (y/n) ";
                std::string str;
                std::cin>>str;
                response = str[0];
            }

        }
        for(auto card : cardsIdx) {
            attackingCreatures.push_back(playables.at(card));
            if(!dynamic_cast<Creature*>(seekCard(playables.at(card)))->hasStaticAbility(StaticAbility::VIGILANCE))
                seekCard(playables.at(card))->tap();
        }
    }
}

std::vector<uint16_t> Battlefield::getAttackingCreatures() {
    
    return attackingCreatures;
}


void Battlefield::setBlockingCreatures(std::vector<Creature *> attacking) {
    blockingCreatures.clear();
    std::vector<uint16_t> playables;
    for(auto creature : getCreatures())
        if(!creature->isTapped()) 
            playables.push_back(creature->getCardUuid());

    char response = 0;
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
        for(size_t i = 0; i < attacking.size(); i += 1) {
            std::cout<<"Attacking creature : ";
            std::cout<<attacking.at(i)->getName()<<attacking.at(i)->getTmpStats()<<std::endl;

            std::vector<uint16_t> blockable;
            for(auto creature : getCreatures()) {
                if(attacking.at(i)->hasStaticAbility(StaticAbility::INTIMIDATE)) {
                    bool similarColors = false;
                    for(auto attackingColor : attacking.at(i)->getCost())
                        for(auto blockingColor : creature->getCost())
                            if(attackingColor.first == blockingColor.first && attackingColor.first != Color::WBBRG)
                                similarColors = true;
                    if(!similarColors) continue;
                }
                bool isAlreadyBlocking = false;
                for(auto vect : blockingCreatures)
                    if(std::find(vect.begin(), vect.end(), creature->getCardId()) != vect.end()) isAlreadyBlocking = true;
                
                if(!isAlreadyBlocking && 
                   !creature->isTapped() &&
                   !attacking.at(i)->hasStaticAbility(StaticAbility::CANT_BE_BLOCKED) &&
                  (!attacking.at(i)->hasStaticAbility(StaticAbility::FLY) || (creature->hasStaticAbility(StaticAbility::FLY) || creature->hasStaticAbility(StaticAbility::REACH))))
                    blockable.push_back(creature->getCardUuid());
            }

            std::cout<<"Available for blocking : "<<blockable.size()<<std::endl;
            for(size_t j = 0; j < blockable.size(); j += 1)
                std::cout <<"   "<< j << " - " << seekCard(blockable.at(j))->getName() << dynamic_cast<Creature*>(seekCard(blockable.at(j)))->getTmpStats() << std::endl;
            
            char blockResponse = 0;
            while (blockResponse != 'y' && blockResponse != 'n' && blockable.size() > 0)
            {

                std::cout<<"Do you want to block this card with something ? (y/n) ";
                std::string str;
                std::cin>>str;
                blockResponse = str[0];

            }

            std::vector<uint16_t> cardsIdx;
            while (response == 'y' && cardsIdx.size() < blockable.size())
            {
                int choice = -1;
                while (choice < 0 || choice >= (int)blockable.size())
                {
                    std::string str;
                    std::cout<<"Choose card to play : ";
                    std::cin>>str;
                    try {
                        choice = std::stoi(str);
                        if(std::find(cardsIdx.begin(), cardsIdx.end(), choice) != cardsIdx.end()) {
                            std::cout<<"You already block with this card"<<std::endl;
                            choice = -1;
                        }
                            
                    }
                    catch (const std::exception) {
                        std::cout << "Invalid argument : " << str << std::endl;
                    }
                }
                
                cardsIdx.push_back(blockable.at((uint16_t)choice));
                response = 0;
                while (response != 'y' && response != 'n' && cardsIdx.size() < playables.size())
                {
                    std::cout<<"Do you want to attack with another card ? (y/n) ";
                    std::string str;
                    std::cin>>str;
                    response = str[0];
                }

            }
            blockingCreatures.push_back(cardsIdx);
        }
    } else {
        for(size_t i = 0; i<attacking.size(); i += 1)
        {
            std::vector<uint16_t> cardsIdx;
            blockingCreatures.push_back(cardsIdx);
        }
        
    }


}

std::vector<std::vector<uint16_t> > Battlefield::getBlockingCreatures() {
    return blockingCreatures;
}

void Battlefield::tapColors(const std::map<Color, int>& cost) {
    for(auto colorCost : cost) {
        if(colorCost.first != Color::WBBRG) {
            for(int j = 0; j < colorCost.second; j += 1) {
                auto it = std::find_if(lands.begin(), lands.end(), [&](const std::unique_ptr<Land>& x) { return !x->isTapped() && colorCost.first == x->getColor();});
                (*it)->tap();
            }
        }else {
            for(int i = 0; i < colorCost.second; i += 1) {

                std::vector<Land*> remainingLands;
                std::set<Color> remainingColors;
                for(auto& land : lands)
                    if(!land->isTapped()) {
                        remainingLands.push_back(land.get());
                        remainingColors.insert(land.get()->getColor());
                    }
                if(remainingColors.size() == 1 || remainingLands.size() == (size_t)colorCost.second - i) {
                    remainingLands.at(0)->tap();
                }else {
                    std::cout<<"Please select a land. Remaining : " << colorCost.second - i<<std::endl;
                    for(size_t j = 0; j < remainingLands.size(); j += 1)
                        std::cout << "  "<< j <<" - "<<remainingLands.at(j)->getName()<<std::endl;
                    
                    int choice = -1;
                    while (choice < 0 || choice >= (int)remainingLands.size())
                    {
                        std::string str;
                        std::cout<<"Choose land to tap : ";
                        std::cin>>str;
                        try {
                            choice = std::stoi(str);
                        }
                        catch (const std::exception) {
                            std::cout << "Invalid argument : " << str << std::endl;
                        }
                    }
                    remainingLands.at(choice)->tap();
                }
            }

        }
    }

}