#pragma once
#include "Block.h"
class SpeedUpBlock :
    public Block
{
public:
    SpeedUpBlock(const sf::Vector2f& size, const sf::Vector2f& pos) :
        Block(size, pos, TYPE::SPEED_UP) {};

};

