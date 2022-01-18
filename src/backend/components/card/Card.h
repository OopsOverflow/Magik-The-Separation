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
enum class Color{WHITE, BLUE, BLACK, RED, GREEN, WBBRG};


class Card {
public:
    Card(uint8_t id, const std::string &name, std::unordered_map<Color, int> cost);

    virtual const std::string &getName() const;

    virtual void setName(const std::string &name);

    virtual const std::unordered_map<Color, int> &getCost() const;

    virtual void setCost(const std::unordered_map<Color, int> &cost);
    bool isAffordable(std::vector<Color> availableMana);

    virtual ~Card();

    uint8_t getCardUuid() const;
    uint8_t getCardId() const;

    bool isTapped() const; //TODO (only permanent can be tapped)
    void unTap();
private:
    std::string name;
    std::unordered_map<Color, int> cost;

    bool tapped;
    uint8_t uuid;
    uint8_t id;

    static uint8_t nextCardId;

};


#endif //MAGIK_CARD_H
