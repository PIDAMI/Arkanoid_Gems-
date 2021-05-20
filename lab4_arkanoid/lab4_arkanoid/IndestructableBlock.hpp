#pragma once
#include "Block.hpp"
class IndestructableBlock :
    public Block
{
public:
    IndestructableBlock(const sf::Vector2f& size, const sf::Vector2f& pos) :
        Block(size, pos, TYPE::INDESTRUCTABLE, sf::Color::Magenta) {};
    virtual int ReduceHealth() { return -1; }
};

