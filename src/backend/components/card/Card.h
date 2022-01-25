//
// Created by houssem on 04/01/2022.
//
#ifndef MAGIK_CARD_H
#define MAGIK_CARD_H


#include <string>
#include <map>
#include <vector>

// Suckless
typedef uint16_t sint;
enum class CardType {CREATURE, ENCHANTEMENT, INSTANT, LAND, SORCERY};
enum class Color{WHITE, BLUE, BLACK, RED, GREEN, WBBRG};
enum class StaticAbility{FLY, REACH, VIGILANCE, DEATHTOUCH, DEFENDER, FIRST_STRIKE, DOUBLE_STRIKE, HASTE, CANT_BE_BLOCKED, LIFELINK, INTIMIDATE, TRAMPLE};


class Card {
public:
    Card(uint16_t id, std::string name, std::map<Color, int> cost);

    virtual const std::string &getName() const;
    virtual const std::map<Color, int> &getCost() const;

    bool isAffordable(std::vector<Color> availableMana);

    virtual ~Card();

    uint16_t getCardUuid() const;
    uint16_t getCardId() const;

    bool isTapped() const; //TODO (only permanent can be tapped)
    void unTap();
    void tap();
private:
    std::string name;
    std::map<Color, int> cost;

    bool tapped;
    uint16_t uuid;
    uint16_t id;

    static uint16_t nextCardId;

};


#endif //MAGIK_CARD_H
