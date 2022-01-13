//
// Created by pierre on 05/01/2022.
//

#include "Player.h"

uint64_t Player::newId = 0;

Player::Player(std::string name, std::vector<std::unique_ptr<Card>> &deck, std::shared_ptr<Stack> stack)
:   name(name), id(newId), hp(20), canCastInstant(false),
    library(deck), graveyard(), exile(), hand(), battlefield(), stack(std::move(stack)) {
    newId += 1;
}


Player::~Player() {

}

std::string Player::getName() const {
    return name;
}

uint64_t Player::getId() const {
    return id;
}

int8_t Player::getHp() const {
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

Exile* Player::getExile() {
    return &exile;
}

void Player::draw(uint8_t numberOfCards) {
    if(library.getLenght() <= 1){
        hp = 0;
    }else {
        hand.add(std::move(library.getTopCard()));
    }    
}

void Player::summonCard(uint8_t cardNumber) {
    std::unique_ptr<Card> card = std::move(hand.popCard(cardNumber));
    if(false) {//TODO if is a land
        battlefield.add(std::move(card));
    }else{
        stack->add(std::move(card));
    }

}


void Player::unTapAll() {
    for(int i = 0; i < battlefield.getLenght(); i += 1) {
        battlefield.unTap(i); //TODO only cards that can be tapped
    }
}

bool Player::castSpellOrAbility() {
    bool hasCastedNow = false;
    //TODO (Player can play cards)
    return hasCastedNow;

}

void Player::takeDamage(uint8_t amount) {
    hp -= amount;
}