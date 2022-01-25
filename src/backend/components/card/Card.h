//
// Created by houssem on 04/01/2022.
//
#ifndef MAGIK_CARD_H
#define MAGIK_CARD_H


#include <string>
#include <unordered_map>

// Suckless
typedef uint8_t sint;

class Card {
public:
    Card(const std::string &name, std::unordered_map<std::string, int> cost);

    virtual const std::string &getName() const;

    virtual void setName(const std::string &name);

    virtual const std::unordered_map<std::string, int> &getCost() const;

    virtual void setCost(const std::unordered_map<std::string, int> &cost);

    virtual ~Card();

    virtual bool isTapped() const; //TODO (only permanent can be tapped)
    virtual void unTap();
private:
    std::string name;
    std::unordered_map<std::string, int> cost;

    bool tapped;

};


#endif //MAGIK_CARD_H
