#include "Gem.h"


using namespace std;

void Gem::SetColor(COLORS color) {
	if (color == COLORS::BLUE)
		setFillColor(sf::Color::Blue);
	if (color == COLORS::GREEN)
		setFillColor(sf::Color::Green);
	if (color == COLORS::RED)
		setFillColor(sf::Color::Red);
	if (color == COLORS::CYAN)
		setFillColor(sf::Color::Cyan);
	if (color == COLORS::BLACK)
		setFillColor(sf::Color::Black);
	if (color == COLORS::MAGENTA)
		setFillColor(sf::Color::Magenta);
}


Gem::Gem(float x, float y, int size, COLORS color) {
	setPosition({ x,y });
	setSize(sf::Vector2f(size,size));
	SetColor(color);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(1.5f);
	_bonus = nullptr;
}


bool Gem::SetRandomBonus() {
	
	int bonus_threshold = rand() % 100;
	if (bonus_threshold < BONUS_CHANCE) {
		if (bonus_threshold % 2)
			_bonus = std::make_shared<Bonus>(Bomb());
		else
			_bonus = std::make_shared<Bonus>(Paint());
		return true;
	}
	return false;
}

vector<sf::Vector2i> Gem::ActivateBonus(const sf::Vector2i& board_size,
										const sf::Vector2i& pos) {
	auto affected_gems = _bonus->Activate(board_size, pos);
	return affected_gems;
}

