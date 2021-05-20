#pragma once
#include "SFML/Graphics.hpp"



class Bar: sf::RectangleShape
{
private:
	bool _ball_stick;
	float _speed;
	sf::Vector2f _start_pos;

public:
	Bar(const sf::Vector2f& size, const sf::Vector2f& pos,
		sf::Color c = sf::Color::Blue, float speed = DEFAULT_BAR_SPEED);
	void SetSize(const sf::Vector2f& size) { setSize(size); }
	void SetColor(sf::Color c) { setFillColor(c); };
	void Move();
	bool IsBallStick() const { return _ball_stick; };
	float GetSpeed() const { return _speed; };
	void SetSpeed(float speed) { _speed = speed; };
	void SetBallStick(bool ball_stick) { _ball_stick = ball_stick; };
	void Respawn() { setPosition(_start_pos); };
	void Draw(std::shared_ptr<sf::RenderWindow> window) { window->draw(*this); };
	sf::Vector2f GetCoord() const { return getPosition(); };
	sf::Vector2f GetSize() const { return getSize(); };
	static const float DEFAULT_BAR_SPEED;
};

