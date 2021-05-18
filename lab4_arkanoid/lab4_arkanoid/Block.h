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


class Block:public sf::RectangleShape
{
private:
	int _health;
	sf::Vector2f size;
	enum class TYPE _type;
	int _move_dir;

private:
	const static int MAX_HEALTH;
public:
	Block(const sf::Vector2f& size,const sf::Vector2f& pos, 
		enum class TYPE type = TYPE::NORMAL,sf::Color c = sf::Color::Green);
	Block() :_health(MAX_HEALTH), size({ 40.f,40.f }), _type(TYPE::NORMAL), _move_dir(1)
	{};
	virtual int ReduceHealth();
	int GetHealth() const { return _health; };
	virtual ~Block() {};
	virtual void Move() {}
	TYPE GetType() const { return _type; };
	void SetDirection(int dir) { if (dir == 1 || dir == -1) _move_dir = dir; };
	int GetDirection() const { return _move_dir; };
	virtual sf::Vector2f GetSpeedIncrement() const { return { 0.f,0.f }; };
};





