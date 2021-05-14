#pragma once
#include "SFML/Graphics.hpp"




class Bar;
class Block;

class Ball: public sf::CircleShape
{
private:

	sf::Vector2i _move_dir; // has values 1 and -1
	sf::Vector2f _speed;
	sf::Vector2f _start_coord;

	bool _stick_to_board;
	bool _reflects_bottom;
	bool _random_reflection;

public:
	static const sf::Vector2f DEFAULT_BALL_SPEED;
	static const int RANDOM_REFLECT_CHANCE;

public:

	Ball(float rad, const sf::Vector2f& pos,const sf::Color& col = sf::Color::Blue);
	sf::Vector2f GetTopCoord() const;
	sf::Vector2f GetBottomCoord() const;
	sf::Vector2f GetRightCoord() const;
	sf::Vector2f GetLeftCoord() const;
	bool IsReflectableByBot() const { return _reflects_bottom; };
	bool IsStickToBoard() const { return _stick_to_board; };

	void SetRandReflection(bool refl) { _random_reflection = refl; };
	void SetStickToBoard(bool stick) { _stick_to_board = stick; };
	void SetBottomReflection(bool refl) { _reflects_bottom = refl; };
	void SetSpeed(const sf::Vector2f& speed) { _speed = speed; }
	
	bool ReflectFromBlock(const Block& block);
	void ReflectWall(int window_width);
	void Move(int window_width);
	void RandomlyReflect();
	void MoveWithBar(int window_width);
	void ReflectBar(const Bar& bar);
	void RespawnBall();
	void SpeedUp(const sf::Vector2f increment); // cannot slow

};

