//
// Created by pierre on 05/01/2022.
//

#include "Player.h"

uint64_t Player::newId = 0;

Player::Player(std::string name) 
: name(name), id(newId), hp(20) {
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