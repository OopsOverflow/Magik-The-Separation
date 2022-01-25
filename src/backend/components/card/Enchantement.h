//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_ENCHANTEMENT_H
#define MAGIK_ENCHANTEMENT_H

#include "Card.h"
#include "../ability/ActivatedAbility.h"
#include "../ability/TriggeredAbility.h"

#include <functional>
#include <vector>

class Enchantement : public Card {
public :
    Enchantement(uint16_t id, const std::string &name, std::map<Color, int> cost);
    ~Enchantement();

    Enchantement(Enchantement const&) = delete;
    Enchantement& operator=(Enchantement const&) = delete;

    void addStaticAbility(StaticAbility ability);
    void addActivatedAbility(std::function<void()> ability);
    void addTriggeredAbility(std::function<void(Event)> ability);

    std::vector<std::function<void(Event)> > getTriggerAbilities() const;

private:
    std::vector<StaticAbility> staticAbilities;
    std::vector<std::function<void()> > activatedAbilities;
    std::vector<std::function<void(Event)> > triggeredAbilities;

};


#endif //MAGIK_ENCHANTEMENT_H
