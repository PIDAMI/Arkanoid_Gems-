#include "MovingBlock.h"


void MovingBlock::Move(int window_width) {
    // change direction if touches walls
    if (getPosition().x <= 0 || getPosition().x + getSize().x >= window_width)
        SetDirection(GetDirection() * -1);
   
    move({ GetDirection() * _speed , 0 });
}
