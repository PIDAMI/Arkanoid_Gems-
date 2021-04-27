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

class Gem: sf::RectangleShape{

private:

	COLORS _color;
	std::shared_ptr<Bonus> _bonus;

private:

	void set_bonus(std::shared_ptr<Bonus> bonus) { _bonus = bonus; }

public:

	Gem(float x, float y, int size, COLORS color = COLORS::NUM_COLORS);
	//Gem(std::vector<COLORS> allowed_colors);
	int get_size() { return getSize().x; };
	COLORS get_color() const { return _color;}
	void set_color(COLORS new_color);
	bool has_bonus() { return _bonus != nullptr; };
	bool set_random_bonus();

};


