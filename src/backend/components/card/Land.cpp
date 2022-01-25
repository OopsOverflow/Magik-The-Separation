//
// Created by houssem on 04/01/2022.
//

#include "Land.h"


Land::Land(uint16_t id, const std::string &name, Color color) : Card(id, name, {}), color(color) {

}

Land::~Land() {
    
}

Color Land::getColor() const {
    return color;
}