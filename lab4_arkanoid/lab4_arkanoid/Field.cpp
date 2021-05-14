#include "Field.h"
#include "IndestructableBlock.h"
#include "SpeedUpBlock.h"
using namespace sf;


// 480 x 400
// 3 x 6
// 480 / 6, 400 / 3


const int Field::INDESTRCTABLE_BLOCK_SPAWN_CHANCE = 10;
const int Field::SPEEDUP_BLOCK_SPAWN_CHANCE = 8;
const int Field::BONUS_BLOCK_SPAWN_CHANCE = 5;


Field::Field(const sf::Vector2f& top, const sf::Vector2i& grid_size,
	const sf::Vector2f& window_size, const sf::Vector2f& block_size) {

	_size = grid_size;
	_pos = top;

	float x = top.x;
	float y = top.y;
	_grid.resize(grid_size.x, std::vector<std::shared_ptr<Block>>(grid_size.y));

	for (int i = 0; i < grid_size.x; i++) {
		
		
		for (int j = 0; j < grid_size.y; j++) {
			
			std::shared_ptr<Block> block;
			int block_type = rand() % 100;

			// todo bonuses
			if (block_type < BONUS_BLOCK_SPAWN_CHANCE) {
				//block = std::make_shared<Block>
				//	(new IndestructableBlock(block_size, { x,y }));
			}
			else if (block_type < SPEEDUP_BLOCK_SPAWN_CHANCE) {
				block = std::make_shared<SpeedUpBlock>
					(new SpeedUpBlock(block_size, { x,y }));
			}
			else if (block_type < INDESTRCTABLE_BLOCK_SPAWN_CHANCE) {
				block = std::make_shared<IndestructableBlock>
					(new IndestructableBlock(block_size, { x,y }));
			}
			else {
				block = std::make_shared<Block>
					(new Block(block_size, { x,y }));
			}

			_grid[i][j] = block;

			x += block_size.x;
		}
		y += block_size.y;
	}
}
