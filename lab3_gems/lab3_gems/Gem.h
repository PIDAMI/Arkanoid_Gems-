#pragma once
#include "SFML/Graphics.hpp"
#include "Bonus.h"


class Gem: sf::RectangleShape{

private:

	enum COLORS {
		BLUE,
		GREEN,
		YELLOW,
		RED,
		PURPLE
	};

	COLORS _color;
	Bonus* _bonus;
	bool has_bonus;
	

public:

	Gem();
	Gem(std::vector<COLORS> allowed_colors);
	COLORS get_color() const { return _color;}
	void set_color(COLORS new_color) { _color = new_color; };


};


