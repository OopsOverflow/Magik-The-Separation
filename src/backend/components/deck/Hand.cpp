//
// Created by houssem on 04/01/2022.
//

#include "Hand.h"


Hand::Hand() {
}

Hand::~Hand() {
}

std::unique_ptr<Card> Hand::popCard(uint8_t cardId) {
    for(int i = 0; i < creatures.size(); i += 1) {
        if(creatures.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(creatures.at(i));
            creatures.erase(creatures.begin() + i);
            return ptr;
        }
    }
        
    for(int i = 0; i < lands.size(); i += 1) {
        if(lands.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(lands.at(i));
            lands.erase(lands.begin() + i);
            return ptr;
        }
    }
    
    for(int i = 0; i < enchantements.size(); i += 1) {
        if(enchantements.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(enchantements.at(i));
            enchantements.erase(enchantements.begin() + i);
            return ptr;
        }
    }

    for(int i = 0; i < instants.size(); i += 1) {
        if(instants.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(instants.at(i));
            instants.erase(instants.begin() + i);
            return ptr;
        }
    }

    for(int i = 0; i < sorceries.size(); i += 1) {
        if(sorceries.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(sorceries.at(i));
            sorceries.erase(sorceries.begin() + i);
            return ptr;
        }
    }

    std::cout<< "Error - no card was found in Hand"<< std::endl;
    return nullptr;  
}

Card* Hand::getCard(uint8_t cardId) {
    for(auto const& card : creatures)
        if(card.get()->getCardId() == cardId) return card.get();
    for(auto const& card : instants)
        if(card.get()->getCardId() == cardId) return card.get();
    for(auto const& card : enchantements)
        if(card.get()->getCardId() == cardId) return card.get();
    for(auto const& card : lands)
        if(card.get()->getCardId() == cardId) return card.get();
    for(auto const& card : sorceries)
        if(card.get()->getCardId() == cardId) return card.get();
    
    std::cout<< "Error - no card was found in Hand"<< std::endl;
    return nullptr;
}

uint8_t Hand::getLenght() const {
    return (uint8_t)(creatures.size() + sorceries.size() 
    + lands.size() + instants.size() + enchantements.size());
}


void Hand::add(std::unique_ptr<Card> card) {
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

    case (CardType::SORCERY):
        {
            Sorcery *tmp = dynamic_cast<Sorcery*>(card.get());
            std::unique_ptr<Sorcery> sorcery;
            if(tmp != nullptr)
            {
                card.release();
                sorcery.reset(tmp);
                sorceries.push_back(std::move(sorcery));

            }else {
                std::runtime_error("Error - cast into sorcery in Hand");  
            }
        }
        break;
    
    case (CardType::INSTANT):
        {
            Instant *tmp = dynamic_cast<Instant*>(card.get());
            std::unique_ptr<Instant> instant;
            if(tmp != nullptr)
            {
                card.release();
                instant.reset(tmp);
                instants.push_back(std::move(instant));

            }else {
                std::runtime_error("Error - cast into instant in Hand");  
            }
        }
        break;

    case (CardType::ENCHANTEMENT):
        {
            Enchantement *tmp = dynamic_cast<Enchantement*>(card.get());
            std::unique_ptr<Enchantement> enchantement;
            if(tmp != nullptr)
            {
                card.release();
                enchantement.reset(tmp);
                enchantements.push_back(std::move(enchantement));

            }else {
                std::runtime_error("Error - cast into enchantement in Hand");  
            }
        }
        break;

    default:
        std::runtime_error("Error - cannot find cast in Hand");
        break;
    }
}