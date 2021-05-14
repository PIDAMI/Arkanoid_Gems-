#pragma once
#include "SFML/Graphics.hpp"

#define BONUS_FALL_SPEED 1
#define BONUS_SPAWN_CHANCE 10

enum class BONUS_TYPE {
	BAR_CHANGE,
	SPEED_CHANGE,
	STICK_BAR,
	BOTTOM_REFLECT,
	CHANGE_TRAJECTORY,
	ADDITIONAL_BALL,
	DEFAULT
};

class Field;
class Ball;
class Bar;


class Bonus: public sf::Sprite
{
private:
	enum class BONUS_TYPE _type;
	float _speed;
	sf::Vector2f _size;

public:
	Bonus(sf::Texture texture, sf::Vector2f size,
		BONUS_TYPE type = BONUS_TYPE::DEFAULT, float speed = BONUS_FALL_SPEED) :
		sf::Sprite(texture), _type(type),_speed(speed),_size(size) {};
	
	void Move() { move({ 0,_speed }); };
	virtual void Activate(Field& field, Ball& ball, Bar& bar) = 0;
	bool IsContactedWithBar(const Bar& bar) const;

};

class BarChangeBonus : public Bonus {

private:
	static sf::Texture TEXTURE;

public:
	static void LoadTexture();

public:
	virtual void Activate(Field& field, Ball& ball, Bar& bar) {};
	BarChangeBonus() :
		Bonus(TEXTURE, sf::Vector2f(40.f, 40.f), BONUS_TYPE::BAR_CHANGE) {};
};

class BallSpeedBonus : public Bonus {

};

class BarStickBonus : public Bonus {

};

class BotReflectBonus : public Bonus {

};




