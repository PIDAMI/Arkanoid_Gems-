#pragma once
#include "SFML/Graphics.hpp"


enum class TYPE {
	NORMAL,
	INDESTRUCTABLE,
	SPEED_UP,
	HAS_BONUS,
	DEFAULT
};




class Block:public sf::RectangleShape
{
private:
	int _health;
	sf::Vector2f size;
	enum class TYPE _type;

public:
	Block(const sf::Vector2f& size,const sf::Vector2f& pos, 
		enum class TYPE type = TYPE::NORMAL,sf::Color c = sf::Color::Green);
	virtual int ReduceHealth();
	int GetHealth() const { return _health; };
	virtual ~Block() {};
	const static int MAX_HEALTH;
};

