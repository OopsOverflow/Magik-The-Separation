//
// Created by houssem on 04/01/2022.
//

#include "Instant.h"

Instant::Instant(uint16_t id, const std::string &name, std::map<Color, int> cost) : Card(id, name, cost) {

}

Instant::~Instant() {
    
}