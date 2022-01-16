//
// Created by pierre on 05/01/2022.
//

#include "Player.h"

uint64_t Player::newId = 0;

Player::Player(std::string name, std::shared_ptr<Stack> stack)
:   name(name), id(newId), hp(20), canCastInstant(false),
    library(), graveyard(), hand(), battlefield(), stack(std::move(stack)) {
    newId += 1;
    std::cout<<"Player "<<name<<" created"<<std::endl;
}


Player::~Player() {

}

std::string Player::getName() const {
    return name;
}

uint64_t Player::getId() const {
    return id;
}

int8_t Player::getHp() const {
    return hp;
}

Battlefield* Player::getBattlefield() {
    return &battlefield;
}

Hand* Player::getHand() {
    return &hand;
}

Graveyard* Player::getGraveyard() {
    return &graveyard;
}

Library* Player::getLibrary() {
    return &library;
}

void Player::draw() {
    if(library.getLength() <= 1){
        hp = 0;
    }else {
        auto card = std::move(library.getTopCard());
        std::cout<<"Drawed "<< card.get()->getName()<< std::endl;
        hand.add(std::move(card));
    }    
}

void Player::unTapAll() {
    for(uint8_t i = 0; i < battlefield.getLength(); i += 1) {
        battlefield.unTap(i); //TODO only cards that can be tapped
    }
}

bool Player::castSpellOrAbility() {
    bool hasCastedNow = false;
    stack->display();
    std::cout<<"Playable cards : "<<std::endl;
    int idx = 0;
    for(int i = 0 ; i < hand.getInstants().size(); i += 1) 
        std::cout<< idx++ << " - " << hand.getInstants().at(i)->getName()<<std::endl;
    for(int i = 0; i < battlefield.getCreatures().size(); i += 1) {
        if(battlefield.getCreatures().at(i)->getActivatedAbilities().size() > 0) {
            std::cout<< idx++ << " - " << battlefield.getCreatures().at(i)->getName() <<  " : " << battlefield.getCreatures().at(i)->getActivatedAbilities().size() <<std::endl;
        }
    }
    //TODO enchantments
    char response = 0;
        while (response != 'y' && response != 'n')
        {

            std::cout<< name <<" - Do you want to play something ? (y/n) ";
            std::string str;
            std::cin>>str;
            response = str[0];
        }
    if(response == 'y'){//wantToPlaySmth
        int choice = -1;
        while (choice < 0 || choice >= idx)
        {
            std::string str;
            std::cout<<"Choose card to play : ";
            std::cin>>str;
            try {
                choice = std::stoi(str);
            }
            catch (const std::exception & e) {
                std::cout << "Invalid argument : " << str << std::endl;
            }
        }
        if(choice < hand.getInstants().size()){
            auto card = std::move(hand.summonInstant(choice));
            stack->add(std::move(card));
        }else{
            //TODO play ability
            //TODO play enchantment
        }
        hasCastedNow = true;
    }
    return hasCastedNow;

}

void Player::takeDamage(uint8_t amount) {
    hp -= amount;
}


void Player::setAttackingCards() {

}

std::vector<Creature*> Player::getAttackingCards() {
    std::vector<Creature*> cards;
    return cards;
}

void Player::setBlockingCards(std::vector<Creature*> attackingCards) {

}

std::vector<std::vector<Creature*> > Player::getBlockingCards() {
    std::vector<std::vector<Creature*> > cards;
    return cards;
}


void Player::killCard(Card* cardToKill) {

}