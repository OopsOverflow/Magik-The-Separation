//
// Created by houssem on 04/01/2022.
//

#include "Hand.h"


Hand::Hand() : lands(){
}

Hand::~Hand() {
}

std::unique_ptr<Card> Hand::popCard(uint8_t cardId) {
    for(int i = 0; i < creatures.size(); i += 1)
        if(creatures.at(i)->getCardUuid() == cardId) {
            std::unique_ptr<Card> card = std::move(creatures.at(i));
            creatures.erase(creatures.begin() + i);
            return std::move(card);
        }
            
    for(int i = 0; i < lands.size(); i += 1)
        if(lands.at(i)->getCardUuid() == cardId) {
            std::unique_ptr<Card> card = std::move(lands.at(i));
            lands.erase(lands.begin() + i);
            return std::move(card);
        }

    for(int i = 0; i < instants.size(); i += 1)
        if(instants.at(i)->getCardUuid() == cardId) {
            std::unique_ptr<Card> card = std::move(instants.at(i));
            instants.erase(instants.begin() + i);
            return std::move(card);
        }
        
    for(int i = 0; i < enchantements.size(); i += 1)
        if(enchantements.at(i)->getCardUuid() == cardId) {
            std::unique_ptr<Card> card = std::move(enchantements.at(i));
            enchantements.erase(enchantements.begin() + i);
            return std::move(card);
        }
    
    for(int i = 0; i < sorceries.size(); i += 1)
        if(sorceries.at(i)->getCardUuid() == cardId) {
            std::unique_ptr<Card> card = std::move(sorceries.at(i));
            sorceries.erase(sorceries.begin() + i);
            return std::move(card);
        }

    return nullptr;
}


uint8_t Hand::getLength() const {
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


std::vector<Creature*> Hand::getCreatures() {
    std::vector<Creature*> result;
    for(auto& card : creatures)
        result.push_back(card.get());
    return result;
}

std::vector<Land*> Hand::getLands() {
    std::vector<Land*> result;
    for(int i = 0; i < lands.size(); i += 1)
        result.push_back(lands.at(i).get());
    return result;
}

std::vector<Sorcery*> Hand::getSorceries() {
    std::vector<Sorcery*> result;
    for(auto& card : sorceries)
        result.push_back(card.get());
    return result;
}

std::vector<Enchantement*> Hand::getEnchantements() {
    std::vector<Enchantement*> result;
    for(auto& card : enchantements)
        result.push_back(card.get());
    return result;
}

std::vector<Instant*> Hand::getInstants() {
    std::vector<Instant*> result;
    for(auto& card : instants)
        result.push_back(card.get());
    return result;
}

std::unique_ptr<Creature> Hand::summonCreature(uint8_t id) {
    std::unique_ptr<Creature> card = std::move(creatures.at(id));
    creatures.erase(creatures.begin() + id);
    return std::move(card);
}

std::unique_ptr<Land> Hand::summonLand(uint8_t id) {
    std::unique_ptr<Land> card = std::move(lands.at(id));
    lands.erase(lands.begin() + id);
    return std::move(card);
}

std::unique_ptr<Sorcery> Hand::summonSorcery(uint8_t id) {
    std::unique_ptr<Sorcery> card = std::move(sorceries.at(id));
    sorceries.erase(sorceries.begin() + id);
    return std::move(card);
}

std::unique_ptr<Enchantement> Hand::summonEnchantement(uint8_t id) {
    std::unique_ptr<Enchantement> card = std::move(enchantements.at(id));
    enchantements.erase(enchantements.begin() + id);
    return std::move(card);
}

std::unique_ptr<Instant> Hand::summonInstant(uint8_t id) {
    std::unique_ptr<Instant> card = std::move(instants.at(id));
    instants.erase(instants.begin() + id);
    return std::move(card);
}