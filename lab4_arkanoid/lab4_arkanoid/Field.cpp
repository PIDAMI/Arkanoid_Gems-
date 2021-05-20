#include "Field.h"
#include <iostream>
#include "IndestructableBlock.h"
#include "SpeedUpBlock.h"
#include "MovingBlock.h"
#include "BonusedBlock.h"
#include "Game.h"

using namespace sf;


const int Field::INDESTRCTABLE_BLOCK_SPAWN_CHANCE = 12;
const int Field::SPEEDUP_BLOCK_SPAWN_CHANCE = 10;
const int Field::BONUS_BLOCK_SPAWN_CHANCE = 8;

void Field::Draw(std::shared_ptr<sf::RenderWindow> window) {
	for (const auto& block : _grid) {
		window->draw(*block);
	}
}


void Field::ReduceHealth(unsigned pos) {
	int health_left = _grid[pos]->ReduceHealth();
	if (health_left == 0) {
		_grid.erase(_grid.begin() + pos);
		std::cout << _grid.size() << std::endl;
	}
}

// left blocks are indestructable -> restart
bool Field::CheckGameEnd() const{
	for (const auto& block : _grid) {
		if (block->GetType() != TYPE::INDESTRUCTABLE)
			return false;
	}
	return true;
}


Field::Field(const sf::Vector2f& top,const Vector2u& size,
	const sf::Vector2f& window_size, const sf::Vector2f& block_size) {

	_size = size;
	_pos = top;

	float x = top.x;
	float y = top.y;
	 
	for (int i = 0; i < size.y; i++) {
		for (int j = 0; j < size.x; j++) {
			std::shared_ptr<Block> block;
			int block_type = rand() % 100;

			Vector2f pos = { x,y };
			if (block_type < BONUS_BLOCK_SPAWN_CHANCE) {
				block = std::make_shared<BonusedBlock>
					(BonusedBlock(block_size, pos));
			}
			else if (block_type < SPEEDUP_BLOCK_SPAWN_CHANCE) {
				block = std::make_shared <SpeedUpBlock>
					(SpeedUpBlock(block_size, pos));
			}
			else if (block_type < INDESTRCTABLE_BLOCK_SPAWN_CHANCE) {
				block = std::make_shared <IndestructableBlock>
					(IndestructableBlock(block_size, pos));
			}
			else {
				block = std::make_shared <Block>
					(Block(block_size, pos));
			}

			_grid.push_back(block);
			x += (block_size.x );
		}
		y += (block_size.y);
		x = top.x;
	}
}



bool Field::CheckXForNewMoving(float x, float y) {
	float size = _grid[0]->getSize().x;

	for (auto block : _grid) {
		if (block->getPosition().y == y && 
			(x + block->getSize().x > block->getPosition().x &&
		 	 x < block->getPosition().x + block->getSize().x ||
			(x + block->getSize().x * 1.5f > Game::WINDOW_SIZE.x)))
				return false;
		

		
	}

	return true;
}


void Field::CheckCollisionsBetweenBlocks() {
	for (auto& block1 : _grid) {
		if (block1->GetType() != TYPE::MOVING)
			continue;
		float block1_left_x = block1->getPosition().x;
		float block1_right_x = block1_left_x + block1->getSize().x;
		float block1_top_y = block1->getPosition().y;
		auto block1_type = block1->GetType();

		for (auto& block2 : _grid) {
			if (block2->GetType() != TYPE::MOVING)
				continue;

			float block2_left_x = block2->getPosition().x;
			float block2_right_x = block2_left_x + block2->getSize().x;
			float block2_top_y = block2->getPosition().y;
			auto block2_type = block2->GetType();

			bool collision_block1_left =
				fabs(block1_left_x - block2_right_x) 
				<= MovingBlock::DEFAULT_BLOCK_SPEED;
			bool collision_block2_right = 
				fabs(block1_right_x - block2_left_x)
				<= MovingBlock::DEFAULT_BLOCK_SPEED;
			bool same_y_pos = (block1_top_y == block2_top_y);
			
			if (collision_block1_left && same_y_pos)
				block1->SetDirection(1);
			else if (collision_block2_right && same_y_pos )
				block1->SetDirection(-1);
		}
	}
}


void Field::AddMovingBlock() {
	float block_width = _grid[0]->getSize().x;
	float block_height = _grid[0]->getSize().y;
	float x_pos;
	// checking if there are more moving blocks than number of blocks in a row
	// if so, need to give y_pos a bigger offset from the main grid
	int num_free_line = NumMovingBlocks() % _size.x;
	// spawns in new line; not in line with not moving blocks
	float y_pos = Field::_pos.y + 1.05f * (num_free_line + _size.y) *  block_height;

	do
		x_pos = (float)(rand() % (int)(Game::WINDOW_SIZE.x - block_width));
	while (!CheckXForNewMoving(x_pos, y_pos));
	auto block = std::make_shared <MovingBlock>
		(Vector2f(block_width, block_height), Vector2f(x_pos, y_pos));
	_grid.push_back(block);
}

int Field::NumMovingBlocks() const {
	int i = 0;
	for (const auto& b : _grid) {
		if (b->GetType() == TYPE::MOVING)
			i++;
	}
	return i;
}

void Field::MoveMovingBlocks() {
	for (auto& block : _grid)
		block->Move();
}




