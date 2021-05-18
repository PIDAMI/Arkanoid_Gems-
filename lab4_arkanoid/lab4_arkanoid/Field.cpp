#include "Field.h"
#include <iostream>
#include "IndestructableBlock.h"
#include "SpeedUpBlock.h"
#include "MovingBlock.h"
#include "BonusedBlock.h"

using namespace sf;


const int Field::INDESTRCTABLE_BLOCK_SPAWN_CHANCE = 10;
const int Field::SPEEDUP_BLOCK_SPAWN_CHANCE = 8;
const int Field::BONUS_BLOCK_SPAWN_CHANCE = 5;
//const std::vector<Texture> Field::TEXTURES;


void Field::Draw(RenderWindow& window) {
	for (const auto& block : _grid) {
		window.draw(*block);
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
	 
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			std::shared_ptr<Block> block;
			int block_type = rand() % 100;

			// todo _bonuses
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
			x += block_size.x;
		}
			y += block_size.y;
			x = top.x;
	}
}



bool Field::CheckXForNewMoving(float x, float y, int window_width) {
	for (auto block : _grid)
		if (block->getPosition().y == y)
			
			if (x + block->getSize().x > block->getPosition().x &&
				x < block->getPosition().x + block->getSize().x ||
			   (x + block->getSize().x * 1.5f > window_width))
				return false;
	return true;
}


void Field::CheckCollisionsBetweenBlocks() {
	for (auto block1 : _grid) {

		float block1_left_x = block1->getPosition().x;
		float block1_right_x = block1_left_x + block1->getSize().x;
		float block1_top_y = block1->getPosition().y;
		auto block1_type = block1->GetType();

		for (auto block2 : _grid) {

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
			bool both_moving = 
				(block1_type == TYPE::MOVING) && (block2_type == TYPE::MOVING);

			if (collision_block1_left && same_y_pos && both_moving)
				block1->SetDirection(1);
			else if (collision_block2_right && same_y_pos && both_moving)
				block1->SetDirection(-1);
		}
	}
}


void Field::AddMovingBlock(int window_width) {
	float block_width = _grid[0]->getSize().x;
	float block_height = _grid[0]->getSize().y;
	float x_pos;
	// spawns in new line; not in line with not moving blocks
	float y_pos = Field::_pos.y + 1.05f * _size.y *  block_height;

	do
		x_pos = (float)(rand() % (int)block_width * _size.x);
	while (!CheckXForNewMoving(x_pos, y_pos,window_width));
	auto block = std::make_shared <MovingBlock>
		(Vector2f(block_width, block_height), Vector2f(x_pos, y_pos));
	_grid.push_back(block);
}


void Field::MoveMovingBlocks() {
	for (auto& block : _grid)
		block->Move();
}




