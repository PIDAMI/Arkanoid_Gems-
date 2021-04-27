#pragma once
#include "Board.h"

#define BONUS_CHANCE 5
#define BOMB_TARGETS 5
#define PAINT_TARGETS 3


class Bonus {
protected:
	int _num_affected_gems;
public:
	Bonus():_num_affected_gems(0) {};
	Bonus(int affected_gems_count) :_num_affected_gems(affected_gems_count) {};
	virtual std::vector<sf::Vector2i> activate(const sf::Vector2i& board_size,
		const sf::Vector2i& coord) = 0;
	virtual ~Bonus() {};
};


class Bomb : public Bonus {
public:
	Bomb() :Bonus(BOMB_TARGETS) {};
	virtual std::vector<sf::Vector2i> activate(const sf::Vector2i& board_size,
												const sf::Vector2i& coord);
	~Bomb() {};
};


class Paint : public Bonus {
public:
	Paint() :Bonus(PAINT_TARGETS) {};
	virtual std::vector<sf::Vector2i> activate(const sf::Vector2i& board_size,
											const sf::Vector2i& coord);
	~Paint() {};
};
