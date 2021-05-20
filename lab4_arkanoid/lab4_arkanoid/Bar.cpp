#include "Game.h"

using namespace sf;

const float Bar::DEFAULT_BAR_SPEED = 10.f;

Bar::Bar(const sf::Vector2f& size, const sf::Vector2f& pos, 
        sf::Color c, float speed) {

    _start_pos = pos;
	setPosition(pos);
	setSize(size);
	setFillColor(c);
	_speed = speed;
    _ball_stick = false;

}


void Bar::Move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        if (getPosition().x >= 0)
            move({ -_speed, 0 });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        if (getPosition().x + getSize().x <= Game::WINDOW_SIZE.x)
            move({ _speed, 0 });
    if (_ball_stick)
        // press space to let ball go
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _ball_stick = false;
        }



}




