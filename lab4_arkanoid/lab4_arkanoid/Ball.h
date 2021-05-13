#pragma once
#include "SFML/Graphics.hpp"




class Ball: public sf::CircleShape
{
private:

	sf::Vector2i _move_dir;
	sf::Vector2f _speed;

	bool _stick_to_board;
	bool _reflects_bottom;


public:
	Ball(float rad, const sf::Vector2f& pos,const sf::Color& col = sf::Color::Blue);
	sf::Vector2f GetTopCoord() const;
	sf::Vector2f GetBottomCoord() const;
	sf::Vector2f GetRightCoord() const;
	sf::Vector2f GetLeftCoord() const;
	void Move();
	void ChangeSpeed(const sf::Vector2f& speed) { _speed = speed; }



};

