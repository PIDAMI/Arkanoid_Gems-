#include "Board.h"
#include "Gem.h"

using namespace std;

Board::Board(int dimension, int space, float blockSize, 
			shared_ptr<sf::RenderWindow> window) {
	_window = window;
	_dimension = dimension;
	_space = space;
	_blockSize = blockSize;
	//int top = _space;
	//int left = _space;
	//int width = static_cast<int>(_dimension * _blockSize);
	//int height = width;
	_forDropping.resize(_dimension);
	_blocks.resize(_dimension);


	float x = _space;
	for (int i = 0; i < _dimension; i++) {
		float y = _space;
		for (int j = 0; j < _dimension; j++) {
			auto block = make_shared<Gem>(new Gem(x, y, _blockSize));
			block->set_color(static_cast<COLORS>
				(rand() % static_cast<int>(COLORS::NUM_COLORS)));
			COLORS color;
			do {
				color = (static_cast<COLORS>
					(rand() % static_cast<int>(COLORS::NUM_COLORS)));
			}
			while ((i != 0 && _blocks[i - 1][j]->get_color() == color)
					|| (j != 0 && _blocks[i][j - 1]->get_color() == color));
			block->set_color(color);
			_blocks[i][j] = block;
			y += _blockSize;
		}
		x += _blockSize;
	}
}

// set contains coordinates (x,y) in format <stroke_length> * x + y
// dublicates dont count as it's set, reformatting is bijective
void Board::SearchSequence(sf::Vector2i blockPos, set<int>& SeqElements) {
	if (SeqElements.find(blockPos.x * _dimension + blockPos.y) != SeqElements.end())
		return;
	SeqElements.insert(blockPos.x * _dimension + blockPos.y);
	COLORS color = _blocks[blockPos.x][blockPos.y]->get_color();
	if (blockPos.x != 0 && _blocks[blockPos.x - 1][blockPos.y]->get_color() == color) {
		sf::Vector2i newPosition = { blockPos.x - 1, blockPos.y };
		SearchSequence(newPosition, SeqElements);
	}
	if (blockPos.x != 9 && _blocks[blockPos.x + 1][blockPos.y]->get_color() == color) {
		sf::Vector2i newPosition = { blockPos.x + 1, blockPos.y };
		SearchSequence(newPosition, SeqElements);
	}
	if (blockPos.y != 0 && _blocks[blockPos.x][blockPos.y - 1]->get_color() == color) {
		sf::Vector2i newPosition = { blockPos.x, blockPos.y - 1 };
		SearchSequence(newPosition, SeqElements);
	}
	if (blockPos.y != 9 && _blocks[blockPos.x][blockPos.y + 1]->get_color() == color) {
		sf::Vector2i newPosition = { blockPos.x, blockPos.y + 1 };
		SearchSequence(newPosition, SeqElements);
	}
}

