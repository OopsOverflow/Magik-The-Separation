//
// Created by houssem on 04/01/2022.
//

#include "Instant.h"

Instant::Instant(uint8_t id, const std::string &name, std::unordered_map<Color, int> cost) : Card(id, name, cost) {

}

Instant::~Instant() {
    
}