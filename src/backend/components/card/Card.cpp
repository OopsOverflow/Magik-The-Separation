//
// Created by houssem on 04/01/2022.
//

#include "Card.h"


Card::Card(const std::string &name, const Type &type,
           std::unordered_map<std::string, int> cost) : name(name), type(type), cost(std::move(cost)), tapped(false) {

}

Card::~Card() {

}

const std::string &Card::getName() const {
    return name;
}

void Card::setName(const std::string &name) {
    Card::name = name;
}

const Type &Card::getType() const {
    return type;
}

void Card::setType(const Type &type) {
    Card::type = type;
}

const std::unordered_map<std::string, int> &Card::getCost() const {
    return cost;
}

void Card::setCost(const std::unordered_map<std::string, int> &cost) {
    Card::cost = cost;
}

bool Card::isTapped() const {
    return tapped;
}

void Card::unTap() {
    tapped = false;
}