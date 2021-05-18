#include "MovingBlock.h"

const float MovingBlock::DEFAULT_BLOCK_SPEED = 1.f;

void MovingBlock::Move(int window_width) {
    // change direction if touches walls
    if (getPosition().x <= 0 || getPosition().x + getSize().x >= window_width)
        SetDirection(GetDirection() * -1);
   
    move({ GetDirection() * _speed , 0 });
}
