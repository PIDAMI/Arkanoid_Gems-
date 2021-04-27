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

bool Board::IfSequence(sf::Vector2i blockPos) {
	set<int> SeqElements;
	SearchSequence(blockPos, SeqElements);
	if (SeqElements.size() > 2) {
		for (auto key : SeqElements) {
			// reformat coordinates to vector type
			sf::Vector2i position{ key / _dimension, key % _dimension };
			if (_blocks[position.x][position.y]->has_bonus()) {
				auto BonusDrop = _blocks[position.x][position.y]->BonusActivate(position);
				for (auto drop : BonusDrop)
					_forDropping[drop.x].insert(drop.y);
			}
			_forDropping[position.x].insert(position.y);
		}
		int key = *SeqElements.begin();
		_blocks[key / 10][key % 10]->BonusCover(SeqElements.size());
		SeqElements.clear();
		return true;
	}
	SeqElements.clear();
	return false;
}

void Board::DropStep(vector<int>& forStep) {
	sf::Vector2f speed(0.f, 0.5f);
	for (int i = 0; i < int(_blockSize * 2); i++) {
		for (int j = 0; j < _dimension; j++)
			for (int k = 0; k <= forStep[j]; k++)
				_blocks[j][k]->Moving(speed);
		Draw();
	}
	for (int j = 0; j < _dimension; j++) {
		if (forStep[j] != -1) {
			Block* buf = _blocks[j][forStep[j]];
			for (int k = forStep[j]; k > 0; k--) {
				_blocks[j][k] = _blocks[j][k - 1];
			}
			_blocks[j][0] = buf;
		}
	}
}

void Board::Dropping() {
	vector<int> forStep(_dimension, -1);
	unsigned int step = 1;

	for (int coloumn = 0; coloumn < _dimension; coloumn++) {
		if (_forDropping[coloumn].size() >= step) {
			auto row = _forDropping[coloumn].end();
			row--;
			for (unsigned int i = 1; i <= _forDropping[coloumn].size(); i++, row--) {
				_blocks[coloumn][*row]->Moving(sf::Vector2f{ 0, -(_blockSize * (*row + i)) });
				_blocks[coloumn][*row]->SetVariant(Block_type(rand() % (int)(Block_type::DEFAULT)));
			}
		}
	}
	bool isFalling = true;
	while (isFalling) {
		isFalling = false;
		for (int coloumn = 0; coloumn < _dimension; coloumn++) {
			if (_forDropping[coloumn].size() >= step) {
				isFalling = true;
				auto row = _forDropping[coloumn].end();
				for (unsigned int i = 0; i < step; i++, row--);
				forStep[coloumn] = *row + step - 1;
			}
			else
				forStep[coloumn] = -1;
		}
		DropStep(forStep);
		step++;
	}
	vector<sf::Vector2i> forCheck;
	for (int coloumn = 0; coloumn < _dimension; coloumn++) {
		if (_forDropping[coloumn].size() > 0) {
			auto row = _forDropping[coloumn].end();
			row--;
			for (int i = 0; i <= *row; i++)
				forCheck.push_back(sf::Vector2i{ coloumn, i });
		}
		_forDropping[coloumn].clear();
	}
	IfDropped(forCheck);
}

void Board::Draw() {
	_window->clear(sf::Color::White);
	for (int i = 0; i < _dimension; i++)
		for (int j = 0; j < _dimension; j++) {
			_window->draw(*_blocks[i][j]);
			if (_blocks[i][j]->isBonus())
				_blocks[i][j]->BonusDraw(_window);

		}
	_window->display();
}

void Board::Swap(sf::Vector2i block1, sf::Vector2i block2) {
	sf::Vector2f finish1 = _blocks[block2.x][block2.y]->getPosition();
	sf::Vector2f finish2 = _blocks[block1.x][block1.y]->getPosition();
	sf::Vector2f speed = finish2 - finish1;
	sf::Vector2f delt;
	float distance = sqrtf(speed.x * speed.x + speed.y * speed.y);
	if (distance > _blockSize)
		return;
	while (distance >= 0.03f) {
		_blocks[block1.x][block1.y]->move(-speed * 0.01f);
		_blocks[block2.x][block2.y]->move(speed * 0.01f);
		_window->clear();
		Draw();
		delt = _blocks[block1.x][block1.y]->getPosition() - finish1;
		distance = sqrtf(delt.x * delt.x + delt.y * delt.y);
	}
	_blocks[block2.x][block2.y]->move(finish2 - _blocks[block2.x][block2.y]->getPosition());
	_blocks[block1.x][block1.y]->move(finish1 - _blocks[block1.x][block1.y]->getPosition());
	_window->clear();
	Draw();
	Block* bufBlock = _blocks[block1.x][block1.y];
	_blocks[block1.x][block1.y] = _blocks[block2.x][block2.y];
	_blocks[block2.x][block2.y] = bufBlock;
}


void Board::IfDropped(vector<sf::Vector2i>& forCheck) {
	bool ifSeq = false;
	for (auto pos : forCheck) {
		if (_forDropping[pos.x].find(pos.y) == _forDropping[pos.x].end())
			ifSeq = IfSequence(pos) || ifSeq;
	}
	if (!ifSeq && forCheck.size() == 2)
		Swap(forCheck[0], forCheck[1]);
	forCheck.clear();
	if (ifSeq)
		Dropping();
}

/*Board::~Board() {
	for (int i = 0; i < _dimension; i++)
		for (int j = 0; j < _dimension; j++)
			delete _blocks[i][j];
}*/