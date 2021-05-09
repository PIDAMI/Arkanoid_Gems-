#include "Gem.h"

using namespace std;

void Gem::SetColor(COLORS color) {
	_color = color;
	if (color == COLORS::BLUE)
		setFillColor(sf::Color::Blue);
	else if (color == COLORS::GREEN)
		setFillColor(sf::Color::Green);
	else if (color == COLORS::YELLOW)
		setFillColor(sf::Color::Yellow);
	else if (color == COLORS::WHITE)
		setFillColor(sf::Color::White);
	else if (color == COLORS::RED)
		setFillColor(sf::Color::Red);
	else if (color == COLORS::CYAN)
		setFillColor(sf::Color::Cyan);
	else if (color == COLORS::MAGENTA)
		setFillColor(sf::Color::Magenta);
	
	
}


Gem::Gem(float x, float y, float size, COLORS color) {
	setPosition(x,y);
	setSize(sf::Vector2f(size,size));
	_color = color;
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(-2.5f);
	_bonus = nullptr;
}


bool Gem::SetRandomBonus() {
	
	int bonus_threshold = rand() % 100;
	if (bonus_threshold < BONUS_CHANCE && _bonus == nullptr) {
		if (bonus_threshold % 2)
			_bonus = new Bomb(getPosition());
		else
			_bonus = new Paint(getPosition());
		SetColor(COLORS::BONUS);
		return true;
	}
	return false;
}

vector<sf::Vector2i> Gem::ActivateBonus(const sf::Vector2i& board_size,
										const sf::Vector2i& pos) {
	auto affected_gems = _bonus->Activate(board_size, pos);
	delete _bonus;
	_bonus = nullptr;
	return affected_gems;
}

void Gem::Move(sf::Vector2f speed) {
	move(speed);
	if (HasBonus())
		_bonus->move(speed);
}