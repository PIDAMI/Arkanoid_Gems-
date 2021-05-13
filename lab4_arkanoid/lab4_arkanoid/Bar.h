#pragma once
#include "SFML/Graphics.hpp"


#define DEFAULT_WINDOW_WIDTH 780

class Bar: sf::RectangleShape
{
private:
	bool _ball_stick;
	float _speed;

public:
	Bar(float speed,const sf::Vector2f& size, const sf::Vector2f& pos,
		sf::Color c = sf::Color::Blue);
	void Move(float window_width = DEFAULT_WINDOW_WIDTH);
	bool IsBallStick() const { return _ball_stick; };
	float GetSpeed() const { return _speed; };
	void SetSpeed(float speed) { _speed = speed; };
	void SetBallStick(bool ball_stick) { _ball_stick = ball_stick; };


};

