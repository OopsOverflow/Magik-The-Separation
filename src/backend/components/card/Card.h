//
// Created by houssem on 04/01/2022.
//
#ifndef MAGIK_CARD_H
#define MAGIK_CARD_H


#include <string>
#include <unordered_map>
#include "backend/components/type/Type.h"

// Suckless
typedef u_int8_t sint;

class Card {
public:
    Card(const std::string &name, const Type &type,
         std::unordered_map<std::string, int> cost);

    const std::string &getName() const;

    void setName(const std::string &name);

    const Type &getType() const;

    void setType(const Type &type);

    const std::unordered_map<std::string, int> &getCost() const;

    void setCost(const std::unordered_map<std::string, int> &cost);

    virtual ~Card();

    bool isTapped() const; //TODO (only permanent can be tapped)
    void unTap();
private:
    std::string name;
    Type type;
    std::unordered_map<std::string, int> cost;

    bool tapped;

};


#endif //MAGIK_CARD_H
