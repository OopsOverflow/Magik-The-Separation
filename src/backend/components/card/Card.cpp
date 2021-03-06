//
// Created by houssem on 04/01/2022.
//

#include "Card.h"
#include <algorithm>
#include <utility>

uint16_t Card::nextCardId = 0;

Card::Card(uint16_t id, std::string name, std::map<Color, int> cost) : name(std::move(name)), cost(std::move(cost)), tapped(false), uuid(nextCardId), id(id) {
    nextCardId += 1;
}


Card::~Card() = default;

std::string Card::getColorStr() {
    std::string resultName;
    if(cost.size() > 0) {
        std::string toStr[5] = {"W", "B", "B", "R", "G"};
        for(auto color : cost) {
            if(color.first != Color::WBBRG) {
                for(int j = 0 ; j < color.second; j += 1)
                    resultName += "{" + toStr[(int)color.first] + "}";
            }else{
                resultName += "{" + std::to_string(color.second) + "}";
            }
        }
    }
    return resultName;
}


std::string Card::getName() {
    return name;
}

const std::map<Color, int> &Card::getCost() const {
    return cost;
}

bool Card::isTapped() const {
    return tapped;
}

void Card::unTap() {
    tapped = false;
}

void Card::tap() {
    tapped = true;
}

uint16_t Card::getCardUuid() const {
    return uuid;
}

uint16_t Card::getCardId() const {
    return id;
}

bool Card::isAffordable(std::vector<Color> availableMana) {
    for(auto colorCost : cost) {
        if(colorCost.first != Color::WBBRG) {
            for(int j = 0; j < colorCost.second; j += 1) {
                auto it = std::find(availableMana.begin(), availableMana.end(), colorCost.first);
                if (it != availableMana.end())
                    availableMana.erase(it);
                else
                    return false;
            }
        }else {
            return colorCost.second <= (int)availableMana.size();
        }
    }
    return true;

}