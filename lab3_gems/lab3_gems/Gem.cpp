#include "Gem.h"

using namespace std;

const vector<sf::Color> Gem::AVAILABLE_COLORS = { 
	  sf::Color::Blue, sf::Color::Green, sf::Color::Yellow,
	  sf::Color::Cyan, sf::Color::White, sf::Color::Magenta,
	  sf::Color::Red
};


void Gem::SetColor(COLORS color) {
	_color = color;
	if (color != COLORS::NUM_COLORS)
		setFillColor(AVAILABLE_COLORS[static_cast<int>(color)]);
	
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
			_bonus = std::make_shared<Bomb>(Bomb(getPosition()));
		else
			_bonus = std::make_shared<Paint>(Paint(getPosition()));
		return true;
	}
	return false;
}

vector<sf::Vector2i> Gem::ActivateBonus(const sf::Vector2i& board_size,
										const sf::Vector2i& pos) {
	auto affected_gems = _bonus->Activate(board_size, pos);
	_bonus = nullptr;
	return affected_gems;
}

void Gem::Move(sf::Vector2f speed) {
	move(speed);
}