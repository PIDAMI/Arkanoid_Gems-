#include "Block.h"


using namespace sf;

const int Block::MAX_HEALTH = 3;

Block::Block(const sf::Vector2f& size, const sf::Vector2f& pos,
			enum class TYPE type, sf::Color c) {

	setSize(size);
	setFillColor(c);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(1.5f);
	setPosition(pos);
	_move_dir = -1;
	_health = MAX_HEALTH;
	_type = type;
}



int Block::ReduceHealth() {
	_health--;
	if (_health == 0) {
		setFillColor(Color::White);
	}
	if (_health == MAX_HEALTH - 1) {
		setFillColor(Color::Yellow);
	}
	else if (_health == MAX_HEALTH - 2) {
		setFillColor(Color::Red);
	}


	return _health;
}
