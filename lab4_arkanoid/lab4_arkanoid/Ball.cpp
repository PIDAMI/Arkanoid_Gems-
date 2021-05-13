#include "Ball.h"

using namespace sf;


Ball::Ball(float rad, const sf::Vector2f& pos,
	const sf::Color& col = sf::Color::Blue) {
	
	setRadius(rad);
	setPosition(pos);
	setFillColor(col);
	_stick_to_board = false;
	_reflects_bottom = false;


}


Vector2f Ball::GetTopCoord() const {
	auto pos = getPosition();
	return { pos.x,pos.y + getRadius() };
}

Vector2f Ball::GetLeftCoord() const {
	auto pos = getPosition();
	return { pos.x + getRadius(),pos.y };
}

Vector2f Ball::GetRightCoord() const {
	auto pos = getPosition();
	auto rad = getRadius();
	return { pos.x + rad,pos.y + 2*rad};
}


Vector2f Ball::GetBottomCoord() const {
	auto pos = getPosition();
	auto rad = getRadius();
	return { pos.x + 2*rad,pos.y +rad};
}



void Ball::Move() {
	move({ _move_dir.x * _speed.x,_move_dir.y * _speed.y });
}