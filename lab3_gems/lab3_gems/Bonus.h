#pragma once
#include "Board.h"


class Bonus {
protected:
	int _affected_gems;
public:
	Bonus() = default;
	Bonus(int affected_gems_count) :_affected_gems(affected_gems_count) {};
	virtual void activate(Board& board, sf::Vector2i& coord) = 0;
	virtual ~Bonus() {};
};


class BombBonus : public Bonus {
public:
	BombBonus() :Bonus(5) {};
	virtual void activate(Board& board, sf::Vector2i& coord);
};


class PaintBonus : public Bonus {
public:
	PaintBonus() :Bonus(3) {};
	virtual void activate(Board& board, sf::Vector2i& coord);
};
