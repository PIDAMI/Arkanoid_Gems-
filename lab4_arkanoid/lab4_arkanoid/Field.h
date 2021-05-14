#pragma once
#include "Block.h"
#include <vector>


typedef std::vector<std::vector<std::shared_ptr<Block>>> Grid;

class Field
{
private:
	Grid _grid;
	sf::Vector2i _size;
	sf::Vector2f _pos;
public:
	const static int INDESTRCTABLE_BLOCK_SPAWN_CHANCE;
	const static int SPEEDUP_BLOCK_SPAWN_CHANCE;
	const static int BONUS_BLOCK_SPAWN_CHANCE;

public:
	//todo: Field contructor
	Field(const sf::Vector2f& top, const sf::Vector2i& grid_size,
		const sf::Vector2f& window_size, const sf::Vector2f& block_size);


};

