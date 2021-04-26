#include "Gem.h"



void Gem::set_color(COLORS color) {
	if (color == COLORS::BLUE)
		setFillColor(sf::Color::Blue);
	if (color == COLORS::GREEN)
		setFillColor(sf::Color::Green);
	if (color == COLORS::RED)
		setFillColor(sf::Color::Red);
	if (color == COLORS::WHITE)
		setFillColor(sf::Color::White);

}

Gem::Gem(float x, float y, int size, COLORS color = COLORS::WHITE) {
	setPosition({ x,y });
	setSize({ size,size });
	set_color(color);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(1.5f);
	_bonus = nullptr;
}


bool Gem::set_random_bonus() {
	
	int bonus_threshold = rand() % 100;
	if (bonus_threshold < BONUS_CHANCE) {
		if (bonus_threshold % 2)
			set_bonus(std::make_shared<Bonus>(new BombBonus));
		else
			set_bonus(std::make_shared<Bonus>(new PaintBonus));
		return true;
	}
	return false;
}

