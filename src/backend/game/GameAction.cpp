//
// Created by houssem on 04/01/2022.
//

#include "GameAction.h"

GameAction& GameAction::getInst() {
    static GameAction gameAction;
    return gameAction;
}

GameAction::GameAction() : phase(Phase::UPKEEP_STEP), turn(1), hasPlayedLand(false) {

}

GameAction::~GameAction() {

}


Phase GameAction::getPhase() const {
    return phase;
}

void GameAction::nextPhase() {
    if(phase == Phase::CLEANUP_STEP) turn += 1;

    phase = (Phase)(((int)phase + 1) % 12);
    if(turn == 1 && phase == Phase::DRAW_STEP) nextPhase();

}

uint8_t GameAction::getTurn() const{
    return turn;
}