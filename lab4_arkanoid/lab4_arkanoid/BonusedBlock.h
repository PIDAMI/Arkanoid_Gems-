#pragma once
#include "Block.h"
#include "Bonus.h"
class BonusedBlock : public Block{
private:
    std::shared_ptr<Bonus> _bonus;

private:
    std::shared_ptr<Bonus> GenerateRandomBonus();

public:
 /*   BonusedBlock(const sf::Vector2f& size, const sf::Vector2f& pos) :
        Block(size, pos), _bonus(std::make_shared<Bonus>(new Bonus()))*/


};

