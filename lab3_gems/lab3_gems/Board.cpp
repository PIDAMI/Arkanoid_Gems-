#include "Board.h"
#include "Gem.h"

using namespace std;

Board::Board(int dimension, int space, float block_size, 
			shared_ptr<sf::RenderWindow> window) {
	_window = window;
	_dimension = dimension;
	_space = space;
	_block_size = block_size;
	//int top = _space;
	//int left = _space;
	//int width = static_cast<int>(_dimension * _block_size);
	//int height = width;
	_forDropping.resize(_dimension);
	_blocks.resize(_dimension);


	float x = _space;
	for (int i = 0; i < _dimension; i++) {
		float y = _space;
		for (int j = 0; j < _dimension; j++) {
			auto block = make_shared<Gem>(new Gem(x, y, _block_size));
			block->SetColor(static_cast<COLORS>
				(rand() % static_cast<int>(COLORS::NUM_COLORS)));
			COLORS color;
			do {
				color = (static_cast<COLORS>
					(rand() % static_cast<int>(COLORS::NUM_COLORS)));
			}
			while ((i != 0 && _blocks[i - 1][j]->GetColor() == color)
					|| (j != 0 && _blocks[i][j - 1]->GetColor() == color));
			block->SetColor(color);
			_blocks[i][j] = block;
			y += _block_size;
		}
		x += _block_size;
	}
}

// set contains coordinates (x,y) in format <stroke_length> * x + y
// dublicates dont count as it's set, reformatting is bijective
void Board::SearchSequence(sf::Vector2i block_pos, set<int>& seq_elems) {
	if (seq_elems.find(block_pos.x * _dimension + block_pos.y) != seq_elems.end())
		return;
	seq_elems.insert(block_pos.x * _dimension + block_pos.y);
	COLORS color = _blocks[block_pos.x][block_pos.y]->GetColor();
	if (block_pos.x != 0 && _blocks[block_pos.x - 1][block_pos.y]->GetColor() == color) {
		sf::Vector2i newPosition = { block_pos.x - 1, block_pos.y };
		SearchSequence(newPosition, seq_elems);
	}
	if (block_pos.x != 9 && _blocks[block_pos.x + 1][block_pos.y]->GetColor() == color) {
		sf::Vector2i newPosition = { block_pos.x + 1, block_pos.y };
		SearchSequence(newPosition, seq_elems);
	}
	if (block_pos.y != 0 && _blocks[block_pos.x][block_pos.y - 1]->GetColor() == color) {
		sf::Vector2i newPosition = { block_pos.x, block_pos.y - 1 };
		SearchSequence(newPosition, seq_elems);
	}
	if (block_pos.y != 9 && _blocks[block_pos.x][block_pos.y + 1]->GetColor() == color) {
		sf::Vector2i newPosition = { block_pos.x, block_pos.y + 1 };
		SearchSequence(newPosition, seq_elems);
	}
}

bool Board::IfSequence(sf::Vector2i block_pos) {
	set<int> seq_elems;
	SearchSequence(block_pos, seq_elems);
	if (seq_elems.size() >= 3) {
		for (auto key : seq_elems) {
			sf::Vector2i position{ key / 10, key % 10 };
			if (_blocks[position.x][position.y]->HasBonus()) {
				vector<sf::Vector2i> BonusDrop = 
					_blocks[position.x][position.y]->
					ActivateBonus(sf::Vector2i(_dimension,_dimension),position);
				for (auto drop : BonusDrop)
					_forDropping[drop.x].insert(drop.y);
			}
			_forDropping[position.x].insert(position.y);
		}
		int key = *seq_elems.begin();
		_blocks[key / 10][key % 10]->SetRandomBonus();
		seq_elems.clear();
		return true;
	}
	seq_elems.clear();
	return false;
}



void Board::DropStep(vector<int>& forStep) {
	sf::Vector2f speed(0.0f, 0.5f);
	for (int i = 0; i < int(_block_size * 2); i++) {
		for (int j = 0; j < _dimension; j++)
			for (int k = 0; k <= forStep[j]; k++)
				_blocks[j][k]->Move(speed);
		Draw();
	}
	for (int j = 0; j < _dimension; j++) {
		if (forStep[j] != -1) {
			auto buf = _blocks[j][forStep[j]];
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
				_blocks[coloumn][*row]
					->Move(sf::Vector2f{ 0, -(_block_size * (*row + i)) });
				_blocks[coloumn][*row]->
					SetColor(COLORS(rand() % (int)(COLORS::NUM_COLORS)));
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
	vector<sf::Vector2i> for_check;
	for (int coloumn = 0; coloumn < _dimension; coloumn++) {
		if (_forDropping[coloumn].size() > 0) {
			auto row = _forDropping[coloumn].end();
			row--;
			for (int i = 0; i <= *row; i++)
				for_check.push_back(sf::Vector2i{ coloumn, i });
		}
		_forDropping[coloumn].clear();
	}
	IfDropped(for_check);
}

void Board::Draw() {
	_window->clear(sf::Color::White);
	for (int i = 0; i < _dimension; i++)
		for (int j = 0; j < _dimension; j++) {
			_window->draw(*_blocks[i][j]);
			//if (_blocks[i][j]->HasBonus())
			//	_blocks[i][j]->BonusDraw(_window);

		}
	_window->display();
}

void Board::Swap(sf::Vector2i block1, sf::Vector2i block2) {
	sf::Vector2f finish1 = _blocks[block2.x][block2.y]->getPosition();
	sf::Vector2f finish2 = _blocks[block1.x][block1.y]->getPosition();
	sf::Vector2f speed = finish2 - finish1;
	sf::Vector2f delt;
	float distance = sqrtf(speed.x * speed.x + speed.y * speed.y);
	if (distance > _block_size)
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
	auto bufBlock = _blocks[block1.x][block1.y];
	_blocks[block1.x][block1.y] = _blocks[block2.x][block2.y];
	_blocks[block2.x][block2.y] = bufBlock;
}


void Board::IfDropped(vector<sf::Vector2i>& for_check) {
	bool ifSeq = false;
	for (auto pos : for_check) {
		if (_forDropping[pos.x].find(pos.y) == _forDropping[pos.x].end())
			ifSeq = IfSequence(pos) || ifSeq;
	}
	if (!ifSeq && for_check.size() == 2)
		Swap(for_check[0], for_check[1]);
	for_check.clear();
	if (ifSeq)
		Dropping();
}

