#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Bonus.h"


enum class COLORS {
	BLUE,
	GREEN,
	YELLOW,
	CYAN,
	MAGENTA,
	RED,
	BLACK,
	NUM_COLORS
};

class Gem: public sf::RectangleShape{

private:

	COLORS _color;
	std::shared_ptr<Bonus> _bonus;

private:

	//void set_bonus(std::shared_ptr<Bonus> bonus) { _bonus = bonus; }

public:

	Gem(float x, float y, int size, COLORS color = COLORS::NUM_COLORS);
	//Gem(std::vector<COLORS> allowed_colors);
	//int GetSize() { return getSize().x; };
	std::shared_ptr<Bonus> GetBonus() const { return _bonus; };
	Gem(const Gem& g) :_color(g.GetColor()), _bonus(g.GetBonus()) {};
	COLORS GetColor() const { return _color; };
	void SetColor(COLORS new_color);
	bool HasBonus() { return _bonus != nullptr; };
	bool SetRandomBonus();
	std::vector<sf::Vector2i> ActivateBonus(const sf::Vector2i& board_size,
											const sf::Vector2i& pos);
	void Move(sf::Vector2f speed) { move(speed);};
	
};


