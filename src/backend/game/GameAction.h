//
// Created by houssem on 04/01/2022.
//

#ifndef MAGIK_GAMEACTION_H
#define MAGIK_GAMEACTION_H


enum class Phase{BEGINNING_PHASE, FIRST_MAIN_PHASE, COMBAT_PHASE, SECOND_MAIN_PHASE, ENDING_PHASE};

class GameAction {
public:
    static GameAction& getInst();
    
    Phase getPhase() const;
    void setPhase(Phase const& phase);

private:
    GameAction();
    ~GameAction();

    Phase phase;
    
};


#endif //MAGIK_GAMEACTION_H
