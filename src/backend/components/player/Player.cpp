//
// Created by pierre on 05/01/2022.
//

#include "Player.h"

uint64_t Player::newId = 0;

Player::Player(std::string name, std::vector<std::unique_ptr<Card> >deck) 
: name(name), id(newId), hp(20), canCastInstant(false),
library(deck), graveyard(), exile(), hand(), battlefield() {
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

Battlefield Player::getBattlefield() const {
    return battlefield;
}

Hand Player::getHand() const {
    return hand;
}

Graveyard Player::getGraveyard() const {
    return graveyard;
}

Library Player::getLibrary() const {
    return library;
}

Exile Player::getExile() const {
    return exile;
}

void Player::allowCastInstant() {
    canCastInstant = true;
}

bool Player::wantCastInstant() const {
    return canCastInstant;
}

void Player::draw(uint8_t numberOfCards) {
    if(library.getLenght() <= 1){
        hp = 0;
    }else {
        hand.add(library.getTopCard());
    }    
}