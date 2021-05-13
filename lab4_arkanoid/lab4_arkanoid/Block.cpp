#include "Block.h"


using namespace sf;


Block::Block(const sf::Vector2f& size, const sf::Vector2f& pos,
			enum class TYPE type, sf::Color c) {

	setSize(size);
	setFillColor(c);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(0.5f);
	setPosition(pos);
	_health = MAX_BLOCK_HEALTH;
	_type = type;
}



virtual int Block::ReduceHealth() {
	_health--;
	if (_health == 0) {
		setFillColor(Color::White);
	}
	if (_health == MAX_BLOCK_HEALTH - 1) {
		setFillColor(Color::Yellow);
	}
	else if (_health == MAX_BLOCK_HEALTH - 2) {
		setFillColor(Color::Red);
	}


	return _health;
}
