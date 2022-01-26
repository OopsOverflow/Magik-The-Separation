//
// Created by pierre on 05/01/2022.
//

#include "Player.h"

uint64_t Player::newId = 0;

Player::Player(const std::string& name)
:   name(name), id(newId), hp(20),
    battlefield(), hand(), graveyard(), library() {
    newId += 1;
    std::cout<<"Player "<<name<<" created"<<std::endl;
}


Player::~Player() {

}

std::string Player::getName() const {
    return name + "(" + std::to_string(hp) + ")";
}

uint64_t Player::getId() const {
    return id;
}

int Player::getHp() const {
    return hp;
}

Battlefield* Player::getBattlefield() {
    return &battlefield;
}

Hand* Player::getHand() {
    return &hand;
}

Graveyard* Player::getGraveyard() {
    return &graveyard;
}

Library* Player::getLibrary() {
    return &library;
}

void Player::draw() {
    if(library.getLength() <= 1){
        hp = 0;
    }else {
        auto card = std::move(library.getTopCard());
        std::cout<<"Drawed "<< card.get()->getName()<< std::endl;
        hand.add(std::move(card));
    }    
}

void Player::unTapAll() {
    for(size_t i = 0; i < battlefield.getCreatures().size(); i += 1) {
        battlefield.getCreatures().at(i)->unTap();
        battlefield.getCreatures().at(i)->newTurn();
    }

    
    for(size_t i = 0; i < battlefield.getLands().size(); i += 1)
        battlefield.getLands().at(i)->unTap();
}

void Player::takeDamage(int amount) {
    hp -= amount;
}

void Player::heal(int amount) {
    hp += amount;
}

void Player::killCard(uint16_t cardId) {
    std::unique_ptr<Card> card;
    if(hand.seekCard(cardId) != nullptr)
        card = std::move(hand.popCard(cardId));
    else
        card = std::move(battlefield.popCard(cardId));
    graveyard.add(std::move(card));
}

std::vector<uint16_t> Player::getCastableInstantsOrAbilities() {
    std::vector<uint16_t> result;
    std::vector<Color> availableMana;
    auto lands = battlefield.getLands();
    for(size_t i = 0; i < lands.size(); i += 1) {
        if(!lands.at(i)->isTapped())
            availableMana.push_back(lands.at(i)->getColor());
    }
    
    auto instants = hand.getInstants();
    for(size_t i = 0 ; i < instants.size(); i += 1) {
        if(instants.at(i)->isAffordable(availableMana))
            result.push_back(instants.at(i)->getCardUuid());
    }

    auto creatures = battlefield.getCreatures();
    for(size_t i = 0; i < creatures.size(); i += 1) {
        for(size_t j = 0; j < creatures.at(i)->getActivatedAbilities().size(); j += 1) {
            if(creatures.at(i)->getActivatedAbilities().at(j).isAffordable(availableMana) && !creatures.at(i)->isTapped() && !creatures.at(i)->isSummoned())
                result.push_back(creatures.at(i)->getActivatedAbilities().at(j).getCardUuid());
        }
    }
    //TODO enchantments
    return result;
}

std::vector<uint16_t> Player::getPlayableCards(bool hasPlayedLand) {
    std::vector<uint16_t> result;
    std::vector<Color> availableMana;
    auto lands = battlefield.getLands();
    for(size_t i = 0; i < lands.size(); i += 1) {
        if(!lands.at(i)->isTapped())
            availableMana.push_back(lands.at(i)->getColor());
    }

    if(!hasPlayedLand) {
        auto _lands = hand.getLands();
        for(size_t i = 0; i < _lands.size(); i += 1)
            result.push_back(_lands.at(i)->getCardUuid());
    }

    auto creatures = hand.getCreatures();
    for(size_t i = 0; i < creatures.size(); i += 1)
        if(creatures.at(i)->isAffordable(availableMana))
            result.push_back(creatures.at(i)->getCardUuid());
    
    auto enchants = hand.getEnchantements();
    for(size_t i = 0; i < enchants.size(); i += 1)
        if(enchants.at(i)->isAffordable(availableMana))
            result.push_back(enchants.at(i)->getCardUuid());
    
    auto sorceries = hand.getSorceries();
    for(size_t i = 0; i < sorceries.size(); i += 1)
        if(sorceries.at(i)->isAffordable(availableMana))
            result.push_back(sorceries.at(i)->getCardUuid());

    auto abilities = getCastableInstantsOrAbilities();
    result.insert(result.end(), abilities.begin(), abilities.end());
    return result;
}

Card* Player::seekCard(uint16_t cardId) {
    Card* result = hand.seekCard(cardId);
    if(result != nullptr) return result;

    return battlefield.seekCard(cardId);
}

std::unique_ptr<Card> Player::playCard(uint16_t cardId) {
    std::unique_ptr<Card> card = hand.popCard(cardId);
    if(card != nullptr) 
        return card; // TODO : CHECK MOVE HERE
    
    auto creatures = battlefield.getCreatures();
    //TODO add attached enchants
    return nullptr;
}