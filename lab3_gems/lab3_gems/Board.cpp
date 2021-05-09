#include "Board.h"
#include "Bonus.h"
#include "Gem.h"

using namespace std;

Board::Board(int dimension, int space, float block_size, sf::RenderWindow* window) {
	_window = window;
	_dimension = dimension;
	_space = space;
	_block_size = block_size;
	top = _space;
	left = _space;
	width = static_cast<int>(_dimension * _block_size);
	height = width;
	_for_dropping.resize(_dimension, set<int>());
	_gems.resize(_dimension, vector<std::shared_ptr<Gem>>(_dimension));


	float x = (float)_space;
	for (int i = 0; i < _dimension; i++) {
		float y = (float)_space;
		for (int j = 0; j < _dimension; j++) {
			auto block = make_shared<Gem>(Gem(x, y, _block_size));
			COLORS color;
			do {
				color = (static_cast<COLORS>
					(rand() % static_cast<int>(COLORS::NUM_COLORS)));
			}
			while ((i != 0 && _gems[i - 1][j]->GetColor() == color)
					|| (j != 0 && _gems[i][j - 1]->GetColor() == color));
			block->SetColor(color);
			_gems[i][j] = block;
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
	COLORS color = _gems[block_pos.x][block_pos.y]->GetColor();
	if (block_pos.x != 0) {
		auto neighbor = _gems[block_pos.x - 1][block_pos.y]->GetColor();
		if (neighbor == color || neighbor == COLORS::BONUS) {
			sf::Vector2i new_pos = { block_pos.x - 1, block_pos.y };
			SearchSequence(new_pos, seq_elems);

		}
	}
	if (block_pos.x != _dimension-1) {
		auto neighbor = _gems[block_pos.x + 1][block_pos.y]->GetColor();
		if (neighbor == color || neighbor == COLORS::BONUS) {
			sf::Vector2i new_pos = { block_pos.x + 1, block_pos.y };
			SearchSequence(new_pos, seq_elems);
		}
	}
	if (block_pos.y != 0 && _gems[block_pos.x][block_pos.y - 1]->GetColor() == color) {
		auto neighbor = _gems[block_pos.x][block_pos.y - 1]->GetColor();
		if (neighbor == color || neighbor == COLORS::BONUS) {
			sf::Vector2i new_pos = { block_pos.x, block_pos.y - 1};
			SearchSequence(new_pos, seq_elems);
		}
	}
	if (block_pos.y != _dimension - 1) {
		auto neighbor = _gems[block_pos.x][block_pos.y + 1]->GetColor();
		if (neighbor == color || neighbor == COLORS::BONUS) {
			sf::Vector2i new_pos = { block_pos.x, block_pos.y + 1};
			SearchSequence(new_pos, seq_elems);

		}
	}
}

bool Board::IsColorMatch(const sf::Vector2i& gem_pos, const sf::Vector2i& neighbor) const {

}


//bool Board::IfSequence(sf::Vector2i blockPos) {
//	set<int> SeqElements;
//	SearchSequence(blockPos, SeqElements);
//	if (SeqElements.size() >= 3) {
//		for (auto key : SeqElements) {
//			sf::Vector2i position{ key / 10, key % 10 };
//			if (_gems[position.x][position.y]->HasBonus()) {
//				vector<sf::Vector2i> BonusDrop = 
//					_gems[position.x][position.y]
//					->ActivateBonus(sf::Vector2i(_dimension,_dimension),position);
//				for (auto drop : BonusDrop)
//					_for_dropping[drop.x].insert(drop.y);
//			}
//			_for_dropping[position.x].insert(position.y);
//		}
//		int key = *SeqElements.begin();
//		_gems[key / 10][key % 10]->SetRandomBonus();
//		SeqElements.clear();
//		return true;
//	}
//	SeqElements.clear();
//	return false;
//}


bool Board::IfSequence(sf::Vector2i block_pos) {
	set<int> seq_elems;
	SearchSequence(block_pos, seq_elems);
	if (seq_elems.size() >= DROP_THRESHOLD) {

		for (auto key : seq_elems) {
			sf::Vector2i position{ key / _dimension, key % _dimension };
			if (_gems[position.x][position.y]->HasBonus()) {
				auto bonus_targets = _gems[position.x][position.y]->
					ActivateBonus(sf::Vector2i(_dimension, _dimension), position);
				for (auto drop : bonus_targets)
					_for_dropping[drop.x].insert(drop.y);
			}
			_for_dropping[position.x].insert(position.y);
		}
		if (seq_elems.size() >= COMBO_SIZE_BONUS)
		{
			int key = *seq_elems.begin();
			_gems[key / _dimension][key % _dimension]->SetRandomBonus();
		}
		seq_elems.clear();
		return true;
	}

	seq_elems.clear();
	return false;
}



void Board::DropStep(vector<int>& forStep) {
	sf::Vector2f speed(0.f, 0.5f);
	for (int i = 0; i < int(_block_size * 2); i++) {
		for (int j = 0; j < _dimension; j++) {
			for (int k = 0; k <= forStep[j]; k++)
				_gems[j][k]->Move(speed);
		}
		Draw();
	}
	for (int j = 0; j < _dimension; j++) {
		if (forStep[j] != -1) {
			auto buf = _gems[j][forStep[j]];
			for (int k = forStep[j]; k > 0; k--) {
				_gems[j][k] = _gems[j][k - 1];
			}
			_gems[j][0] = buf;
		}
	}
}

void Board::Dropping() {
	vector<int> forStep(_dimension, -1);
	unsigned int step = 1;

	for (int coloumn = 0; coloumn < _dimension; coloumn++) {
		if (_for_dropping[coloumn].size() >= step) {
			auto row = _for_dropping[coloumn].end();
			row--;
			for (unsigned int i = 1; i <= _for_dropping[coloumn].size(); i++, row--) {
				_gems[coloumn][*row]
					->Move(sf::Vector2f( 0, -(_block_size * (*row + i)) ));
				_gems[coloumn][*row]->SetColor(static_cast<COLORS>
						(rand() % static_cast<int>(COLORS::NUM_COLORS)));
			}
		}
	}
	bool isFalling = true;
	while (isFalling) {
		isFalling = false;
		for (int coloumn = 0; coloumn < _dimension; coloumn++) {
			if (_for_dropping[coloumn].size() >= step) {
				isFalling = true;
				auto row = _for_dropping[coloumn].end();
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
		if (_for_dropping[coloumn].size() > 0) {
			auto row = _for_dropping[coloumn].end();
			row--;
			for (int i = 0; i <= *row; i++)
				for_check.push_back(sf::Vector2i{ coloumn, i });
		}
		_for_dropping[coloumn].clear();
	}
	IfDropped(for_check);
}

void Board::Draw() {
	_window->clear(sf::Color::White);
	for (int i = 0; i < _dimension; i++) {
		for (int j = 0; j < _dimension; j++) {
			_window->draw(*_gems[i][j]);
			if (_gems[i][j]->HasBonus())
				_gems[i][j]->BonusDraw(_window);
		}
	}
	_window->display();
}

void Board::Swap(sf::Vector2i block1, sf::Vector2i block2) {
	sf::Vector2f finish1 = _gems[block2.x][block2.y]->getPosition();
	sf::Vector2f finish2 = _gems[block1.x][block1.y]->getPosition();
	sf::Vector2f speed = finish2 - finish1;
	sf::Vector2f delt;
	float distance = sqrtf(speed.x * speed.x + speed.y * speed.y);
	if (distance > _block_size)
		return;
	while (distance >= 0.03f) {
		_gems[block1.x][block1.y]->move(-speed * 0.01f);
		_gems[block2.x][block2.y]->move(speed * 0.01f);
		_window->clear();
		Draw();
		delt = _gems[block1.x][block1.y]->getPosition() - finish1;
		distance = sqrtf(delt.x * delt.x + delt.y * delt.y);
	}
	_gems[block2.x][block2.y]->move(finish2 - _gems[block2.x][block2.y]->getPosition());
	_gems[block1.x][block1.y]->move(finish1 - _gems[block1.x][block1.y]->getPosition());
	_window->clear();
	Draw();
	//std::swap(_gems[block1.x][block1.y], _gems[block2.x][block2.y]);
	auto bufBlock = _gems[block1.x][block1.y];
	_gems[block1.x][block1.y] = _gems[block2.x][block2.y];
	_gems[block2.x][block2.y] = bufBlock;
}


void Board::IfDropped(vector<sf::Vector2i>& for_check) {
	bool if_seq = false;
	for (auto pos : for_check) {
		if (_for_dropping[pos.x].find(pos.y) == _for_dropping[pos.x].end())
			if_seq = IfSequence(pos) || if_seq;
	}
	if (!if_seq && for_check.size() == 2)
		Swap(for_check[0], for_check[1]);
	for_check.clear();
	if (if_seq)
		Dropping();
}

//Board::Board(int dimension, int space, float gemsize, sf::RenderWindow* window) {
//	_window = window;
//	_dimension = dimension;
//	_space = space;
//	_block_size = gemsize;
//	top = _space;
//	left = _space;
//	width = (int)(_dimension * _block_size);
//	height = (int)(_dimension * _block_size);
//	_for_dropping.resize(_dimension, set<int>());
//	_gems.resize(_dimension, vector<std::shared_ptr<Gem>>(_dimension));
//
//	float x = (float)_space;
//	for (int i = 0; i < _dimension; i++) {
//		float y = (float)_space;
//		for (int j = 0; j < _dimension; j++) {
//			auto block =  std::make_shared<Gem>(Gem(x, y, _block_size));
//			block->SetColor(COLORS(rand() % (int)(COLORS::NUM_COLORS)));
//			COLORS type;
//			do
//				type = COLORS(rand() % (int)(COLORS::NUM_COLORS));
//			while ((i != 0 && _gems[i - 1][j]->GetColor() == type) || (j != 0 && _gems[i][j - 1]->GetColor() == type));
//			block->SetColor(type);
//			_gems[i][j] = block;
//			y += _block_size;
//		}
//		x += _block_size;
//	}
//}
//
//void Board::SearchSequence(sf::Vector2i blockPos, set<int>& SeqElements) {
//	if (SeqElements.find(blockPos.x * 10 + blockPos.y) != SeqElements.end())
//		return;
//	SeqElements.insert(blockPos.x * 10 + blockPos.y);
//	auto type = _gems[blockPos.x][blockPos.y]->GetColor();
//	if (blockPos.x != 0 && _gems[blockPos.x - 1][blockPos.y]->GetColor() == type) {
//		sf::Vector2i newPosition = { blockPos.x - 1, blockPos.y };
//		SearchSequence(newPosition, SeqElements);
//	}
//	if (blockPos.x != 9 && _gems[blockPos.x + 1][blockPos.y]->GetColor() == type) {
//		sf::Vector2i newPosition = { blockPos.x + 1, blockPos.y };
//		SearchSequence(newPosition, SeqElements);
//	}
//	if (blockPos.y != 0 && _gems[blockPos.x][blockPos.y - 1]->GetColor() == type) {
//		sf::Vector2i newPosition = { blockPos.x, blockPos.y - 1 };
//		SearchSequence(newPosition, SeqElements);
//	}
//	if (blockPos.y != 9 && _gems[blockPos.x][blockPos.y + 1]->GetColor() == type) {
//		sf::Vector2i newPosition = { blockPos.x, blockPos.y + 1 };
//		SearchSequence(newPosition, SeqElements);
//	}
//}
//
//bool Board::IfSequence(sf::Vector2i blockPos) {
//	set<int> SeqElements;
//	SearchSequence(blockPos, SeqElements);
//	if (SeqElements.size() >= 3) {
//		for (auto key : SeqElements) {
//			sf::Vector2i position{ key / 10, key % 10 };
//			if (_gems[position.x][position.y]->HasBonus()) {
//				vector<sf::Vector2i> BonusDrop = _gems[position.x][position.y]
//					->ActivateBonus(sf::Vector2i(_dimension,_dimension),position);
//				for (auto drop : BonusDrop)
//					_for_dropping[drop.x].insert(drop.y);
//			}
//			_for_dropping[position.x].insert(position.y);
//		}
//		int key = *SeqElements.begin();
//		_gems[key / 10][key % 10]->SetRandomBonus();
//		SeqElements.clear();
//		return true;
//	}
//	SeqElements.clear();
//	return false;
//}
//
//void Board::DropStep(vector<int>& forStep) {
//	sf::Vector2f speed(0.f, 0.5f);
//	for (int i = 0; i < int(_block_size * 2); i++) {
//		for (int j = 0; j < _dimension; j++)
//			for (int k = 0; k <= forStep[j]; k++)
//				_gems[j][k]->Move(speed);
//		Draw();
//	}
//	for (int j = 0; j < _dimension; j++) {
//		if (forStep[j] != -1) {
//			auto buf = _gems[j][forStep[j]];
//			for (int k = forStep[j]; k > 0; k--) {
//				_gems[j][k] = _gems[j][k - 1];
//			}
//			_gems[j][0] = buf;
//		}
//	}
//}
//
//void Board::Dropping() {
//	vector<int> forStep(_dimension, -1);
//	unsigned int step = 1;
//
//	for (int coloumn = 0; coloumn < _dimension; coloumn++) {
//		if (_for_dropping[coloumn].size() >= step) {
//			auto row = _for_dropping[coloumn].end();
//			row--;
//			for (unsigned int i = 1; i <= _for_dropping[coloumn].size(); i++, row--) {
//				_gems[coloumn][*row]->Move(sf::Vector2f{ 0, -(_block_size * (*row + i)) });
//				//_gems[coloumn][*row]->SetVariant(Block_type(rand() % (int)(Block_type::DEFAULT)));
//				_gems[coloumn][*row]->
//					SetColor(COLORS(rand()%(int)(COLORS::NUM_COLORS)));
//			}
//		}
//	}
//	bool isFalling = true;
//	while (isFalling) {
//		isFalling = false;
//		for (int coloumn = 0; coloumn < _dimension; coloumn++) {
//			if (_for_dropping[coloumn].size() >= step) {
//				isFalling = true;
//				auto row = _for_dropping[coloumn].end();
//				for (unsigned int i = 0; i < step; i++, row--);
//				forStep[coloumn] = *row + step - 1;
//			}
//			else
//				forStep[coloumn] = -1;
//		}
//		DropStep(forStep);
//		step++;
//	}
//	vector<sf::Vector2i> forCheck;
//	for (int coloumn = 0; coloumn < _dimension; coloumn++) {
//		if (_for_dropping[coloumn].size() > 0) {
//			auto row = _for_dropping[coloumn].end();
//			row--;
//			for (int i = 0; i <= *row; i++)
//				forCheck.push_back(sf::Vector2i{ coloumn, i });
//		}
//		_for_dropping[coloumn].clear();
//	}
//	IfDropped(forCheck);
//}
//
//void Board::Draw() {
//	_window->clear(sf::Color::White);
//	for (int i = 0; i < _dimension; i++)
//		for (int j = 0; j < _dimension; j++) {
//			_window->draw(*_gems[i][j]);
//			if (_gems[i][j]->HasBonus())
//				_gems[i][j]->BonusDraw(_window);
//
//		}
//	_window->display();
//}
//
//void Board::Swap(sf::Vector2i block1, sf::Vector2i block2) {
//	sf::Vector2f finish1 = _gems[block2.x][block2.y]->getPosition();
//	sf::Vector2f finish2 = _gems[block1.x][block1.y]->getPosition();
//	sf::Vector2f speed = finish2 - finish1;
//	sf::Vector2f delt;
//	float distance = sqrtf(speed.x * speed.x + speed.y * speed.y);
//	if (distance > _block_size)
//		return;
//	while (distance >= 0.03f) {
//		_gems[block1.x][block1.y]->move(-speed * 0.01f);
//		_gems[block2.x][block2.y]->move(speed * 0.01f);
//		_window->clear();
//		Draw();
//		delt = _gems[block1.x][block1.y]->getPosition() - finish1;
//		distance = sqrtf(delt.x * delt.x + delt.y * delt.y);
//	}
//	_gems[block2.x][block2.y]->move(finish2 - _gems[block2.x][block2.y]->getPosition());
//	_gems[block1.x][block1.y]->move(finish1 - _gems[block1.x][block1.y]->getPosition());
//	_window->clear();
//	Draw();
//	auto bufBlock = _gems[block1.x][block1.y];
//	_gems[block1.x][block1.y] = _gems[block2.x][block2.y];
//	_gems[block2.x][block2.y] = bufBlock;
//}
//
//
//void Board::IfDropped(vector<sf::Vector2i>& forCheck) {
//	bool ifSeq = false;
//	for (auto pos : forCheck) {
//		if (_for_dropping[pos.x].find(pos.y) == _for_dropping[pos.x].end())
//			ifSeq = IfSequence(pos) || ifSeq;
//	}
//	if (!ifSeq && forCheck.size() == 2)
//		Swap(forCheck[0], forCheck[1]);
//	forCheck.clear();
//	if (ifSeq)
//		Dropping();
//}
