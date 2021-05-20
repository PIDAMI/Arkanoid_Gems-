#pragma once
#include "Block.hpp"
class MovingBlock :
    public Block
{
private:
    float _speed;
public:
    static const float DEFAULT_BLOCK_SPEED;
public:
    MovingBlock(const sf::Vector2f& size, const sf::Vector2f& pos) :
        Block(size, pos, TYPE::MOVING), _speed(DEFAULT_BLOCK_SPEED) {};

    virtual void Move();
};

