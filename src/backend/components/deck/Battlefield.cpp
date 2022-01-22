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
