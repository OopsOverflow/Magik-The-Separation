//
// Created by houssem on 04/01/2022.
//

#include "GameAction.h"

GameAction& GameAction::getInst() {
    static GameAction gameAction;
    return gameAction;
}

GameAction::GameAction() : phase(Phase::FIRST_MAIN_PHASE) {

}

GameAction::~GameAction() {

}


Phase GameAction::getPhase() const {
    return phase;
}

void GameAction::setPhase(Phase const& phase) {
    this->phase = phase;
}