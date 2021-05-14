#pragma once
#include "SFML/Graphics.hpp"



class Bar: sf::RectangleShape
{
private:
	bool _ball_stick;
	float _speed;

public:
	Bar(float speed,const sf::Vector2f& size, const sf::Vector2f& pos,
		sf::Color c = sf::Color::Blue);
	void Move(float window_width);
	bool IsBallStick() const { return _ball_stick; };
	float GetSpeed() const { return _speed; };
	void SetSpeed(float speed) { _speed = speed; };
	void SetBallStick(bool ball_stick) { _ball_stick = ball_stick; };
	sf::Vector2f GetCoord() const { return getPosition(); };
	sf::Vector2f GetSize() const { return getSize(); };
	static const float DEFAULT_BAR_SPEED;
};

