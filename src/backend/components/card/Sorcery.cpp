//
// Created by houssem on 04/01/2022.
//

#include "Sorcery.h"

Sorcery::Sorcery(uint8_t id, const std::string &name, std::map<Color, int> cost) : Card(id, name, cost) {

}

Sorcery::~Sorcery() {
    
}