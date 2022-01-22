//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_CREATURE_H
#define MAGIK_CREATURE_H

#include "Card.h"
#include "../ability/StaticAbility.h"
#include "../ability/ActivatedAbility.h"
#include "../ability/TriggeredAbility.h"
#include "Enchantement.h"

#include <functional>
#include <memory>
#include <vector>

enum class SUBTYPE{ANGEL};

class Creature : public Card {
public :
    Creature(uint8_t id, const std::string &name, std::unordered_map<Color, int> cost, uint8_t power, uint8_t thougness);
    ~Creature();

    Creature(Creature const&) = delete;
    Creature& operator=(Creature const&) = delete;

    uint8_t getPower() const;
    uint8_t getThougness() const;
    

    void block(Creature* attacker);
    void takeDamage(uint8_t damages);

    int8_t getTempDamages() const;

    // void addStaticAbility(std::function<void()> ability);
    // void addActivatedAbility(std::function<void()> ability);
    // void addTriggeredAbility(std::function<void(Event)> ability);

    std::vector<TriggeredAbility > getTriggerAbilities() const;
    std::vector<ActivatedAbility > getActivatedAbilities() const;

    std::vector<Enchantement*> getAttachedCards();
    void attachCard(std::unique_ptr<Enchantement> card);

private :
    uint8_t power;
    uint8_t thougness;

    int8_t tempDamages;

    std::vector<StaticAbility > staticAbilities;//TODO uniqueptr
    std::vector<ActivatedAbility > activatedAbilities;
    std::vector<TriggeredAbility > triggeredAbilities;

    std::vector<std::unique_ptr<Enchantement> > attachedEnchantments;
};


#endif //MAGIK_CREATURE_H
