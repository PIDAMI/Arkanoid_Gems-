#pragma once
#include "SFML/Graphics.hpp"


enum class TYPE {
	NORMAL,
	INDESTRUCTABLE,
	SPEED_UP,
	HAS_BONUS,
	MOVING,
	DEFAULT
};


class Block: public sf::RectangleShape
{
private:
	int _health;
	enum class TYPE _type;
	int _move_dir;

private:
	const static int MAX_HEALTH;
	
public:
	Block(const sf::Vector2f& size,const sf::Vector2f& pos, 
		enum class TYPE type = TYPE::NORMAL,sf::Color c = sf::Color::Green);
	virtual int ReduceHealth();
	int GetHealth() const { return _health; };
	virtual ~Block() {};
	virtual void Move() {};//redefined in moving block class 
	TYPE GetType() const { return _type; };
	void SetDirection(int dir) { if (dir == 1 || dir == -1) _move_dir = dir; };
	int GetDirection() const { return _move_dir; };
	virtual sf::Vector2f GetSpeedIncrement() const { return { 0.f,0.f }; };
};





