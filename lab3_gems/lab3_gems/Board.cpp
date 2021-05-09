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
	if (block_pos.x != 0 && IsColorMatch(block_pos, { block_pos.x - 1,block_pos.y })) {
			sf::Vector2i new_pos = { block_pos.x - 1, block_pos.y };
			SearchSequence(new_pos, seq_elems);
	}
	if (block_pos.x != _dimension-1 && IsColorMatch(block_pos, { block_pos.x + 1,block_pos.y })) {
			sf::Vector2i new_pos = { block_pos.x + 1, block_pos.y };
			SearchSequence(new_pos, seq_elems);
	}
	if (block_pos.y != 0  && IsColorMatch(block_pos, { block_pos.x,block_pos.y-1 })) {
			sf::Vector2i new_pos = { block_pos.x, block_pos.y - 1};
			SearchSequence(new_pos, seq_elems);
	}
	if (block_pos.y != _dimension - 1 && IsColorMatch(block_pos, { block_pos.x ,block_pos.y+1 })) {
			sf::Vector2i new_pos = { block_pos.x, block_pos.y + 1};
			SearchSequence(new_pos, seq_elems);
	}
}

bool Board::IsColorMatch(const sf::Vector2i& gem_pos, const sf::Vector2i& neighbor) const {
	auto color = _gems[gem_pos.x][gem_pos.y]->GetColor();
	auto neigh_color = _gems[neighbor.x][neighbor.y]->GetColor();
	if (color == neigh_color)
		return true;
	return false;

}

bool Board::IfSequence(sf::Vector2i block_pos) {
	set<int> seq_elems;
	SearchSequence(block_pos, seq_elems);
	
	if (seq_elems.size() >= DROP_THRESHOLD) {


		for (auto key : seq_elems) {
			sf::Vector2i position{ key / _dimension, key % _dimension };
			if (_gems[position.x][position.y]->HasBonus()) {
				auto bonus_targets = _gems[position.x][position.y]->
					ActivateBonus(sf::Vector2i(_dimension, _dimension), position);
				if (bonus_targets.size() == BOMB_TARGETS)
					for (auto drop : bonus_targets)
						_for_dropping[drop.x].insert(drop.y);
				else if (bonus_targets.size() == PAINT_TARGETS) {
					for (auto drop : bonus_targets) {
						_gems[drop.x][drop.y]->
							SetColor(_gems[position.x][position.y]->GetColor());
						set<int> bonus_seq_elems;
						SearchSequence(drop, bonus_seq_elems);
					}
				}
			}
			_for_dropping[position.x].insert(position.y);
		}
		if (seq_elems.size() >= COMBO_SIZE_FOR_BONUS)
		{
			int key = *seq_elems.begin();
			int x = key / _dimension;
			int y = key % _dimension;
			auto bonus_pos = ChooseRandInRadius(BONUS_DROP_RADIUS, { x,y });
			_gems[bonus_pos.x][bonus_pos.y]->SetRandomBonus();
		}

		seq_elems.clear();
		return true;
	}

	seq_elems.clear();
	return false;
}

sf::Vector2i Board::ChooseRandInRadius(int radius, sf::Vector2i pos) {
	int dx = pos.x + rand() % radius;
	int dy = pos.y + rand() % radius;
	while (dx < 1 || dy < 1 || dx > _dimension - 2 || dy > _dimension - 2) {
		dx = pos.x;
		dy = pos.y ;
		if (rand() % 2) 
			dx += rand() % radius;
		else 
			dx -= rand() % radius;

		if (rand() % 3) 
			dy -= rand() % radius;
		else 
			dy += rand() % radius;
	}


	return { dx,dy };

}



void Board::DropStep(vector<int>& for_step) {
	sf::Vector2f speed(0.f, 0.25f);
	for (int i = 0; i < int(_block_size * 4); i++) {
		for (int j = 0; j < _dimension; j++) {
			for (int k = 0; k <= for_step[j]; k++)
				_gems[j][k]->Move(speed);
		}
		Draw();
	}
	for (int j = 0; j < _dimension; j++) {
		if (for_step[j] != -1) {
			auto buf = _gems[j][for_step[j]];
			for (int k = for_step[j]; k > 0; k--) {
				_gems[j][k] = _gems[j][k - 1];
			}
			_gems[j][0] = buf;
		}
	}
}

void Board::Dropping() {
	vector<int> for_step(_dimension, -1);
	unsigned int step = 1;

	for (int colomn = 0; colomn < _dimension; colomn++) {
		if (_for_dropping[colomn].size() >= step) {
			auto row = _for_dropping[colomn].end();
			row--;
			for (unsigned int i = 1; i <= _for_dropping[colomn].size(); i++, row--) {
				_gems[colomn][*row]
					->Move(sf::Vector2f( 0, -(_block_size * (*row + i))));
				_gems[colomn][*row]->SetColor(static_cast<COLORS>
						(rand() % static_cast<int>(COLORS::NUM_COLORS)));
			}
		}
	}
	bool is_falling = true;
	while (is_falling) {
		is_falling = false;
		for (int colomn = 0; colomn < _dimension; colomn++) {
			if (_for_dropping[colomn].size() >= step) {
				is_falling = true;
				auto row = _for_dropping[colomn].end();
				for (unsigned int i = 0; i < step; i++, row--);
					for_step[colomn] = *row + step - 1;
			}
			else
				for_step[colomn] = -1;
		}
		DropStep(for_step);
		step++;
	}
	vector<sf::Vector2i> for_check;
	for (int colomn = 0; colomn < _dimension; colomn++) {
		if (_for_dropping[colomn].size() > 0) {
			auto row = _for_dropping[colomn].end();
			row--;
			for (int i = 0; i <= *row; i++)
				for_check.push_back(sf::Vector2i{ colomn, i });
		}
		_for_dropping[colomn].clear();
	}
	IfDropped(for_check);
}


void Board::Draw() {
	_window->clear(sf::Color::White);
	for (int i = 0; i < _dimension; i++) {
		for (int j = 0; j < _dimension; j++) {
				_window->draw(*_gems[i][j]);
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
		_gems[block1.x][block1.y]->Move(-speed * 0.01f);
		_gems[block2.x][block2.y]->Move(speed * 0.01f);
		_window->clear();
		Draw();
		delt = _gems[block1.x][block1.y]->getPosition() - finish1;
		distance = sqrtf(delt.x * delt.x + delt.y * delt.y);
	}
	_gems[block2.x][block2.y]->Move(finish2 - _gems[block2.x][block2.y]->getPosition());
	_gems[block1.x][block1.y]->Move(finish1 - _gems[block1.x][block1.y]->getPosition());
	_window->clear();
	Draw();
	std::swap(_gems[block1.x][block1.y], _gems[block2.x][block2.y]);
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
