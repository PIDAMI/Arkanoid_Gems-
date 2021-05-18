#pragma once
#include "Block.h"
class SpeedUpBlock :
    public Block
{
private:
    sf::Vector2f _speed_increment;
private:
    static const sf::Vector2f DEFAULT_SPEED_INCREMENT;
public:
    SpeedUpBlock(const sf::Vector2f& size, const sf::Vector2f& pos) :
        Block(size, pos, TYPE::SPEED_UP), _speed_increment(DEFAULT_SPEED_INCREMENT)
    {};
    void SetSpeedIncrement(const sf::Vector2f& inc) { _speed_increment = inc; }
    virtual sf::Vector2f GetSpeedIncrement() const { return _speed_increment; }
};

