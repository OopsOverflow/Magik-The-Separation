//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_ENCHANTEMENT_H
#define MAGIK_ENCHANTEMENT_H

#include "Card.h"
#include "../ability/StaticAbility.h"
#include "../ability/ActivatedAbility.h"
#include "../ability/TriggeredAbility.h"

#include <functional>
#include <vector>

class Enchantement : public Card {
public :
    Enchantement(const std::string &name, std::unordered_map<Color, int> cost);
    ~Enchantement();

    Enchantement(Enchantement const&) = delete;
    Enchantement& operator=(Enchantement const&) = delete;

    void addStaticAbility(std::function<void()> ability);
    void addActivatedAbility(std::function<void()> ability);
    void addTriggeredAbility(std::function<void(Event)> ability);

    std::vector<std::function<void(Event)> > getTriggerAbilities() const;

private:
    std::vector<std::function<void()> > staticAbilities;
    std::vector<std::function<void()> > activatedAbilities;
    std::vector<std::function<void(Event)> > triggeredAbilities;

};


#endif //MAGIK_ENCHANTEMENT_H
