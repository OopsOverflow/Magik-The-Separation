//
// Created by pierre on 05/01/2022.
//

#include "Player.h"

uint64_t Player::newId = 0;

Player::Player(std::string name, std::vector<std::unique_ptr<Card> >deck, std::shared_ptr<Stack> stack) 
: name(name), id(newId), hp(20), canCastInstant(false),
library(deck), graveyard(), exile(), hand(), battlefield(), stack(stack) {
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

void Player::setOpponent(Player* player){
    opponent = player;
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

Exile Player::getExile() const {
    return exile;
}

void Player::draw(uint8_t numberOfCards) {
    if(library.getLenght() <= 1){
        hp = 0;
    }else {
        hand.add(library.getTopCard());
    }    
}

void Player::summonCard(uint8_t cardNumber) {
    std::unique_ptr<Card> card = std::move(hand.popCard(cardNumber));
    if(false) {//TODO if is a land
        battlefield.add(std::move(card));
    }else{
        stack->add(std::move(card));
        opponent->castSpellOrAbility(true);
    }

}


void Player::unTapAll() {
    for(int i = 0; i < battlefield.getLenght(); i += 1) {
        battlefield.unTap(i); //TODO only cards that can be tapped
    }
}

void Player::castSpellOrAbility(bool hasCasted) {
    //TODO (Player can play cards)
    bool hasCastedNow = false;
    if (hasCasted || hasCastedNow) opponent->castSpellOrAbility(hasCastedNow);

}

void Player::takeDamage(uint8_t amount) {
    hp -= amount;
}