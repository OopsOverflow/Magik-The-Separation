//
// Created by pierre on 15/01/2022.
//

#ifndef MAGIK_CARDMAKER_H
#define MAGIK_CARDMAKER_H

#include <memory> 
#include <string>
#include <vector>
#include <functional>


#include "Card.h"


class CardMaker {
  
    using Maker = std::function<std::unique_ptr<Card>()>;
    
public:
    
    static CardMaker& getInst();

    int registerCard(const Maker& m);
    std::unique_ptr<Card> create(uint16_t id);
    
private:
    CardMaker();
    std::vector<Maker> factories;
};

#endif //MAGIK_CARDMAKER_H