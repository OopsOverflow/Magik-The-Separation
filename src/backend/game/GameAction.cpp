//
// Created by houssem on 04/01/2022.
//

#include "GameAction.h"
#include <random>

GameAction& GameAction::getInst() {
    static GameAction gameAction;
    return gameAction;
}

GameAction::GameAction() : hasPlayedLand(false), somethingPlayed(true), phase(Phase::UNTAP_STEP), turn(1) {
     std::random_device r;
    
    // Choose a random mean between 0 and 1
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 1);
    rdStart = uniform_dist(e1);
}

GameAction::~GameAction() = default;


Phase GameAction::getPhase() const {
    return phase;
}

void GameAction::nextPhase() {
    if(phase == Phase::CLEANUP_STEP) turn += 1;

    phase = (Phase)(((int)phase + 1) % 12);
    if(turn == 1 && phase == Phase::DRAW_STEP) nextPhase();

}

uint16_t GameAction::getTurn() const{
    return turn;
}