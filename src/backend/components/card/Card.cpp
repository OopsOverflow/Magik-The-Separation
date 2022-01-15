//
// Created by houssem on 04/01/2022.
//

#include "Card.h"

uint8_t Card::nextCardId = 0;

Card::Card(const std::string &name, std::unordered_map<Color, int> cost) : name(name), cost(std::move(cost)), tapped(false), uuid(nextCardId) {
    nextCardId += 1;
}

Card::~Card() {

}

const std::string &Card::getName() const {
    return name;
}

void Card::setName(const std::string &name) {
    Card::name = name;
}

const std::unordered_map<Color, int> &Card::getCost() const {
    return cost;
}

void Card::setCost(const std::unordered_map<Color, int> &cost) {
    Card::cost = cost;
}

bool Card::isTapped() const {
    return tapped;
}

void Card::unTap() {
    tapped = false;
}

uint8_t Card::getCardId() const {
    return uuid;
}