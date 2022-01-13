//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_GAMEACTION_H
#define MAGIK_GAMEACTION_H


enum class Phase{
UNTAP_STEP, UPKEEP_STEP, DRAW_STEP, //BEGINNING PHASE
FIRST_MAIN_PHASE, //FIRST MAIN PHASE
BEGINNING_OF_COMBAT_STEP, DECLARE_ATTACKER_STEP, DECLARE_BLOCKER_STEP, COMBAT_DAMAGE_STEP, END_OF_COMBAT_STEP, //COMBAT PHASE
SECOND_MAIN_PHASE, //SECOND MAIN PHASE
END_STEP, CLEANUP_STEP}; //ENDING PHASE

class GameAction {
public:
    static GameAction& getInst();
    
    Phase getPhase() const;
    void nextPhase(); 
    uint8_t getTurn() const;

    bool hasPlayedLand;

private:
    GameAction();
    ~GameAction();

    Phase phase;
    uint8_t turn;
    
};


#endif //MAGIK_GAMEACTION_H