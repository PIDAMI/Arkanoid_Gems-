#pragma once
#include "Block.h"

class BonusedBlock : public Block{

public:
    BonusedBlock(const sf::Vector2f& size, const sf::Vector2f& pos) :
        Block(size, pos, TYPE::HAS_BONUS) {};
    
    ~BonusedBlock() {};
};

