#include "MovingBlock.hpp"
#include "Game.hpp"

const float MovingBlock::DEFAULT_BLOCK_SPEED = 1.f;

void MovingBlock::Move() {
    // change direction if touches walls
    if (getPosition().x <= 0 || getPosition().x + getSize().x >= Game::WINDOW_SIZE.x)
        SetDirection(GetDirection() * -1);
   
    move({ GetDirection() * _speed , 0 });
}
