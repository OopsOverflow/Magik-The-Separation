//
// Created by houssem on 04/01/2022.
//
#ifndef MAGIK_CARD_H
#define MAGIK_CARD_H


#include <string>
#include <unordered_map>

// Suckless
typedef uint8_t sint;
enum class CardType {CREATURE, ENCHANTEMENT, INSTANT, LAND, SORCERY};


class Card {
public:
    Card(const std::string &name, std::unordered_map<std::string, int> cost);

    virtual const std::string &getName() const;

    virtual void setName(const std::string &name);

    virtual const std::unordered_map<std::string, int> &getCost() const;

    virtual void setCost(const std::unordered_map<std::string, int> &cost);

    virtual ~Card();

    uint8_t getCardId() const;

    virtual bool isTapped() const; //TODO (only permanent can be tapped)
    void unTap();
private:
    std::string name;
    std::unordered_map<std::string, int> cost;

    bool tapped;
    uint8_t uuid;

    static uint8_t nextCardId;

};


#endif //MAGIK_CARD_H
