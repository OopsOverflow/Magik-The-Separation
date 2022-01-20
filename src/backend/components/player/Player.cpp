//
// Created by pierre on 05/01/2022.
//

#include "Player.h"

uint64_t Player::newId = 0;

Player::Player(std::string name)
:   name(name), id(newId), hp(20), canCastInstant(false),
    library(), graveyard(), hand(), battlefield() {
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

// bool Player::castSpellOrAbility() {
//     bool hasCastedNow = false;
//     std::cout<<"Playable cards : "<<std::endl;
//     int idx = 0;
//     for(int i = 0 ; i < hand.getInstants().size(); i += 1) 
//         std::cout<< idx++ << " - " << hand.getInstants().at(i)->getName()<<std::endl;
//     for(int i = 0; i < battlefield.getCreatures().size(); i += 1) {
//         if(battlefield.getCreatures().at(i)->getActivatedAbilities().size() > 0) {
//             std::cout<< idx++ << " - " << battlefield.getCreatures().at(i)->getName() <<  " : " << battlefield.getCreatures().at(i)->getActivatedAbilities().size() <<std::endl;
//         }
//     }
//     //TODO enchantments
//     char response = 0;
//         while (response != 'y' && response != 'n')
//         {

//             std::cout<< name <<" - Do you want to play something ? (y/n) ";
//             std::string str;
//             std::cin>>str;
//             response = str[0];
//         }
//     if(response == 'y'){//wantToPlaySmth
//         int choice = -1;
//         while (choice < 0 || choice >= idx)
//         {
//             std::string str;
//             std::cout<<"Choose card to play : ";
//             std::cin>>str;
//             try {
//                 choice = std::stoi(str);
//             }
//             catch (const std::exception & e) {
//                 std::cout << "Invalid argument : " << str << std::endl;
//             }
//         }
//         if(choice < hand.getInstants().size()){
//             auto card = std::move(hand.summonInstant(choice));
//             stack->add(std::move(card));
//         }else{
//             //TODO play ability
//             //TODO play enchantment
//         }
//         hasCastedNow = true;
//     }
//     return hasCastedNow;

// }

void Player::takeDamage(uint8_t amount) {
    hp -= amount;
}


void Player::killCard(Card* cardToKill) {

}

std::vector<uint8_t> Player::getCastableInstantsOrAbilities() {
    std::vector<uint8_t> result;
    std::vector<Color> availableMana;
    auto lands = battlefield.getLands();
    for(size_t i = 0; i < lands.size(); i += 1) {
        if(!lands.at(i)->isTapped())
            availableMana.push_back(lands.at(i)->getColor());
    }
    
    auto instants = hand.getInstants();
    for(size_t i = 0 ; i < instants.size(); i += 1) {
        if(instants.at(i)->isAffordable(availableMana))
            result.push_back(instants.at(i)->getCardUuid());
    }

    auto creatures = battlefield.getCreatures();
    for(size_t i = 0; i < creatures.size(); i += 1) {
        for(size_t j = 0; j < creatures.at(i)->getActivatedAbilities().size(); j += 1) {
            if(creatures.at(i)->getActivatedAbilities().at(j).isAffordable(availableMana))
                result.push_back(creatures.at(i)->getActivatedAbilities().at(j).getCardUuid());
        }
    }
    //TODO enchantments
    return result;
}

std::vector<uint8_t> Player::getPlayableCards(bool hasPlayedLand) {
    std::vector<uint8_t> result;
    std::vector<Color> availableMana;
    auto lands = battlefield.getLands();
    for(size_t i = 0; i < lands.size(); i += 1) {
        if(!lands.at(i)->isTapped())
            availableMana.push_back(lands.at(i)->getColor());
    }

    if(!hasPlayedLand) {
        auto lands = hand.getLands();
        for(size_t i = 0; i < lands.size(); i += 1)
            result.push_back(lands.at(i)->getCardUuid());
    }

    auto creatures = hand.getCreatures();
    for(size_t i = 0; i < creatures.size(); i += 1)
        if(creatures.at(i)->isAffordable(availableMana))
            result.push_back(creatures.at(i)->getCardUuid());
    
    auto enchants = hand.getEnchantements();
    for(size_t i = 0; i < enchants.size(); i += 1)
        if(enchants.at(i)->isAffordable(availableMana))
            result.push_back(enchants.at(i)->getCardUuid());
    
    auto sorceries = hand.getSorceries();
    for(size_t i = 0; i < sorceries.size(); i += 1)
        if(sorceries.at(i)->isAffordable(availableMana))
            result.push_back(sorceries.at(i)->getCardUuid());

    auto abilities = getCastableInstantsOrAbilities();
    result.insert(result.end(), abilities.begin(), abilities.end());
    return result;
}

Card* Player::seekCard(uint8_t id) {
    auto creatures = hand.getCreatures();
    for(size_t i = 0; i < creatures.size(); i += 1)
        if(creatures.at(i)->getCardUuid() == id)
            return creatures.at(i);

    auto lands = hand.getLands();
    for(size_t i = 0; i < lands.size(); i += 1)
        if(lands.at(i)->getCardUuid() == id)
            return lands.at(i);

    auto instants = hand.getInstants();
    for(size_t i = 0; i < instants.size(); i += 1)
        if(instants.at(i)->getCardUuid() == id)
            return instants.at(i);
        
    auto enchants = hand.getEnchantements();
    for(size_t i = 0; i < enchants.size(); i += 1)
        if(enchants.at(i)->getCardUuid() == id)
            return enchants.at(i);
    
    auto sorceries = hand.getSorceries();
    for(size_t i = 0; i < sorceries.size(); i += 1)
        if(sorceries.at(i)->getCardUuid() == id)
            return sorceries.at(i);

    creatures = battlefield.getCreatures();
    for(size_t i = 0; i < creatures.size(); i += 1) {
        for(size_t j = 0; j < creatures.at(i)->getActivatedAbilities().size(); j += 1) {
            if(creatures.at(i)->getActivatedAbilities().at(j).getCardUuid() == id)
                return creatures.at(i);
        }
    }
    return nullptr;
}

std::unique_ptr<Card> Player::playCard(uint8_t id) {
    std::unique_ptr<Card> card = hand.popCard(id);
    if(card != nullptr) 
        return std::move(card);
    
    auto creatures = battlefield.getCreatures();
    //TODO add attached enchants
// for(int i = 0; i < creatures.size(); i += 1) {
//     for(int j = 0; j < creatures.at(i)->getActivatedAbilities().size(); j += 1) {
//         if(creatures.at(i)->getActivatedAbilities().at(j).getCardUuid() == id)
//             return creatures.at(i)->getName() + "( ability " + std::to_string(j+1) + " )";
//     }
// }
    
    return nullptr;
}

void Player::setAttackingCreatures() {
    attackingCreatures.clear();
    std::vector<uint8_t> playables;
    for(auto creature : battlefield.getCreatures())
        if(!creature->isTapped()) 
            playables.push_back(creature->getCardUuid());

    //TODO can be optimised but don't need to (graphic)
    std::cout<<"Playable creatures : "<<std::endl;
    for(size_t i = 0; i < playables.size(); i += 1)
        std::cout << i << " - " << seekCard(playables.at(i))->getName() << std::endl;    

    char response = 0;//TODO autoscrool at this point
    while (response != 'y' && response != 'n' && playables.size() > 0)
    {

        std::cout<<"Do you want to attack with something ? (y/n) ";
        std::string str;
        std::cin>>str;
        response = str[0];
        if(response == 'y' && playables.size() == 0) {
            std::cout<<"You can't play anything this turn, you should say \"no\""<<std::endl;
            response = 0;
        }
    }
    if(response == 'y') {
        std::vector<uint8_t> cardsIdx;
        while (cardsIdx.size() < playables.size() && response == 'y')
        {
            int choice = -1;
            while (choice < 0 || choice >= (int)playables.size())
            {
                std::string str;
                std::cout<<"Choose card to play : ";
                std::cin>>str;
                try {
                    choice = std::stoi(str);
                    if(std::find(cardsIdx.begin(), cardsIdx.end(), choice) != cardsIdx.end()) {
                        std::cout<<"You already attack with this card"<<std::endl;
                        choice = -1;
                    }
                        
                }
                catch (const std::exception & e) {
                    std::cout << "Invalid argument : " << str << std::endl;
                }
            }
            
            cardsIdx.push_back((uint8_t)choice);
            response = 0;
            while (response != 'y' && response != 'n' && cardsIdx.size() < playables.size())
            {
                std::cout<<"Do you want to attack with another card ? (y/n) ";
                std::string str;
                std::cin>>str;
                response = str[0];
            }

        }
        for(auto card : cardsIdx)
            attackingCreatures.push_back(playables.at(card));
        
    }
}

std::vector<uint8_t> Player::getAttackingCreatures() {
    
    return attackingCreatures;
}


void Player::setBlockingCreatures(std::vector<Creature *> attacking) {
    blockingCreatures.clear();
    std::vector<uint8_t> playables;
    for(auto creature : battlefield.getCreatures())
        if(!creature->isTapped()) 
            playables.push_back(creature->getCardUuid());
    
    std::cout<<"Attacking creatures : "<<std::endl;
    for(size_t i = 0; i < attacking.size(); i += 1)
        std::cout<<i<<" - "<<attacking.at(i)->getName()<<std::endl;

    char response = 0;//TODO autoscrool at this point
    while (response != 'y' && response != 'n' && playables.size() > 0)
    {

        std::cout<<"Do you want to block something ? (y/n) ";
        std::string str;
        std::cin>>str;
        response = str[0];
        if(response == 'y' && playables.size() == 0) {
            std::cout<<"You can't play anything this turn, you should say \"no\""<<std::endl;
            response = 0;
        }
    }

    if(response == 'y') {
        std::vector<uint8_t> cardsIdx;
        while (cardsIdx.size() < playables.size() && response == 'y')
        {
            int choice = -1;
            while (choice < 0 || choice >= (int)playables.size())
            {
                std::string str;
                std::cout<<"Choose card to play : ";
                std::cin>>str;
                try {
                    choice = std::stoi(str);
                    if(std::find(cardsIdx.begin(), cardsIdx.end(), choice) != cardsIdx.end()) {
                        std::cout<<"You already attack with this card"<<std::endl;
                        choice = -1;
                    }
                        
                }
                catch (const std::exception & e) {
                    std::cout << "Invalid argument : " << str << std::endl;
                }
            }
            
            cardsIdx.push_back((uint8_t)choice);
            response = 0;
            while (response != 'y' && response != 'n' && cardsIdx.size() < playables.size())
            {
                std::cout<<"Do you want to attack with another card ? (y/n) ";
                std::string str;
                std::cin>>str;
                response = str[0];
            }

        }
        for(auto card : cardsIdx)
            attackingCreatures.push_back(playables.at(card));
        
    }


}

std::vector<std::vector<uint8_t> > Player::getBlockingCreatures() {
    return blockingCreatures;
}