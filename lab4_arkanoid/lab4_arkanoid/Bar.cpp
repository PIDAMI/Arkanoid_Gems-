#include "Bar.h"



using namespace sf;


const float Bar::DEFAULT_BAR_SPEED = 10.f;

Bar::Bar(float speed, const sf::Vector2f& size, const sf::Vector2f& pos, sf::Color c ) {

	setPosition(pos);
	setSize(size);
	setFillColor(c);
	_speed = speed;
    _ball_stick = false;

}


void Bar::Move(float window_width) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        if (getPosition().x >= 0)
            move({ -_speed, 0 });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        if (getPosition().x + getSize().x <= window_width)
            move({ _speed, 0 });
    if (_ball_stick)
        // press space to let ball go
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            setFillColor(sf::Color::Blue);
            _ball_stick = false;
        }



}




