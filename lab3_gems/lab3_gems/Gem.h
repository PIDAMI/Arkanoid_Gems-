#pragma once
#include <vector>
#include "Bonus.h"


enum class COLORS {
	BLUE,
	GREEN,
	YELLOW,
	CYAN,
	WHITE,
	MAGENTA,
	RED,
	NUM_COLORS
};

class Gem: public sf::RectangleShape{

private:

	COLORS _color;
	std::shared_ptr<Bonus> _bonus;
	//void set_bonus(std::shared_ptr<Bonus> bonus) { _bonus = bonus; }

private:
	static const std::vector<sf::Color> AVAILABLE_COLORS;

public:
	
	Gem(float x = 0.f, float y = 0.f, float size=0.f, COLORS color = COLORS::NUM_COLORS);
	COLORS GetColor() const { return _color; };
	void SetColor(COLORS new_color);
	bool HasBonus() { return _bonus != nullptr; };
	bool SetRandomBonus();
	std::vector<sf::Vector2i> ActivateBonus(const sf::Vector2i& board_size,
											const sf::Vector2i& pos);
	void Move(sf::Vector2f speed);
	void BonusDraw(sf::RenderWindow* window) { window->draw(*_bonus); }
};


