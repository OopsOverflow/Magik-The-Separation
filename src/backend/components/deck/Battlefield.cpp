//
// Created by houssem on 04/01/2022.
//

#include "Battlefield.h"


Battlefield::Battlefield() : Deck() {
}

Battlefield::~Battlefield() {

}

std::unique_ptr<Card> Battlefield::popCard(uint8_t cardId) {
    for(int i = 0; i < creatures.size(); i += 1) {
        if(creatures.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(creatures.at(i));
            creatures.erase(creatures.begin() + i);
            return ptr;
        }

        for(int j = 0; i<creatures.at(i)->getAttachedCards().size(); j += 1) {
            if(creatures.at(i).get()->getAttachedCards().at(j)->getCardId() == cardId) {
                std::unique_ptr<Card> ptr(creatures.at(i)->getAttachedCards().at(j));        //TODO Wip DO NOT WORK
                creatures.at(i)->getAttachedCards().erase(creatures.at(i)->getAttachedCards().begin() + i);
            return ptr;
            }

        }
    }
        
    for(int i = 0; i < lands.size(); i += 1) {
        if(lands.at(i).get()->getCardId() == cardId) {
            std::unique_ptr<Card> ptr = std::move(lands.at(cardId));
            lands.erase(lands.begin() + i);
            return ptr;
        }
    }

    std::cout<< "Error - no card was found in Hand"<< std::endl;
    return nullptr;  
}

Card* Battlefield::getCard(uint8_t cardId) {
    for(auto const& card : creatures)
        if(card.get()->getCardId() == cardId) return card.get();
    for(auto const& card : lands)
        if(card.get()->getCardId() == cardId) return card.get();
    
    std::cout<< "Error - no card was found in Battlefield"<< std::endl;
    return nullptr;
}

uint8_t Battlefield::getLenght() const {
    return (uint8_t) creatures.size() + lands.size();
}


void Battlefield::addCreature(std::unique_ptr<Creature> card) {
    creatures.push_back(std::move(card));
}

void Battlefield::addLand(std::unique_ptr<Land> card) {
    lands.push_back(std::move(card));
}

void Battlefield::addEnchantement(std::unique_ptr<Enchantement> card, Creature* creature) {
    creature->attachCard(std::move(card));
}

void Battlefield::unTap(uint8_t cardNum){
    getCard(cardNum)->unTap();
}    


