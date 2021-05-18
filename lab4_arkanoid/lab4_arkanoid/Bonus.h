#pragma once
#include "SFML/Graphics.hpp"


enum class BONUS_TYPE {
	BAR_CHANGE,
	SPEED_CHANGE,
	STICK_BAR,
	BOTTOM_REFLECT,
	CHANGE_TRAJECTORY,
	MOVING_BLOCK,
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
	sf::Vector2u _size;
private:
	const static float DEFAULT_BONUS_SPEED;
	const static int BONUS_SPAWN_CHANCE;
	const static sf::Vector2u DEFAULT_SPRITE_SIZE;
public:
	// texture's image size = default bonus size, but check anyway 
	Bonus(const sf::Vector2f& pos, const sf::Texture& texture,
		BONUS_TYPE type = BONUS_TYPE::DEFAULT,
		const sf::Vector2u& size = DEFAULT_SPRITE_SIZE,
		float speed = DEFAULT_BONUS_SPEED) :
		sf::Sprite(texture), _type(type),_speed(speed),_size(size)
	{
		setPosition(pos);
		if (texture.getSize() != size) 
			setScale(size.x * 1.0/ texture.getSize().x, size.y * 1.0/ texture.getSize().y);
	};
	
	void Move() { move({ 0,_speed }); };
	virtual void Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
						  std::shared_ptr<Bar> bar) = 0;
	bool IsContactedWithBar(const Bar& bar) const;
	void Draw(sf::RenderWindow& window) { window.draw(*this); };
};

class BarChangeBonus : public Bonus {
private:
	float _size_multiplier;
private:
	const static float DEFAULT_SIZE_MULTIPLIER;
public:
	virtual void Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
		std::shared_ptr<Bar> bar);
	void SetSizeMultiplier(float size_multiplier) { _size_multiplier = size_multiplier; }
	BarChangeBonus(const sf::Vector2f& pos, const sf::Texture& texture) :
		Bonus(pos, texture, BONUS_TYPE::BAR_CHANGE),
		_size_multiplier(DEFAULT_SIZE_MULTIPLIER) {};
};

class BallSpeedBonus : public Bonus {
private:
	float _speed_multiplier;
private:
	const static float DEFAULT_SPEED_MULTIPLIER;
public:
	virtual void Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
		std::shared_ptr<Bar> bar);
	void SetSpeedMultiplier(float multiplier) { _speed_multiplier = multiplier; };
	BallSpeedBonus(const sf::Vector2f& pos, const sf::Texture& texture) :
		Bonus(pos, texture, BONUS_TYPE::SPEED_CHANGE),
		_speed_multiplier(DEFAULT_SPEED_MULTIPLIER) {};

};

class BarStickBonus : public Bonus {
public:
	virtual void Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
		std::shared_ptr<Bar> bar);
	BarStickBonus(const sf::Vector2f& pos, const sf::Texture& texture) :
		Bonus(pos, texture, BONUS_TYPE::STICK_BAR) {};

};


class BotReflectBonus : public Bonus {
public:	
	virtual void Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
						  std::shared_ptr<Bar> bar);
	BotReflectBonus(const sf::Vector2f& pos, const sf::Texture& texture) :
		Bonus(pos, texture, BONUS_TYPE::BOTTOM_REFLECT) {};

};


class ChangeTrajectoryBonus : public Bonus {
public:
	virtual void Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
		std::shared_ptr<Bar> bar);
	ChangeTrajectoryBonus(const sf::Vector2f& pos, const sf::Texture& texture) :
		Bonus(pos, texture, BONUS_TYPE::CHANGE_TRAJECTORY) {};

};


class MovingBlockBonus: public Bonus {
public:
	virtual void Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
		std::shared_ptr<Bar> bar);
	MovingBlockBonus(const sf::Vector2f& pos, const sf::Texture& texture) :
		Bonus(pos, texture, BONUS_TYPE::MOVING_BLOCK) {};

};