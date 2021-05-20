#pragma once
#include "Block.h"
#include <vector>



class Field
{
private:
	std::vector<std::shared_ptr<Block>> _grid;
	sf::Vector2u _size;
	sf::Vector2f _pos;

public:
	const static int INDESTRCTABLE_BLOCK_SPAWN_CHANCE;
	const static int SPEEDUP_BLOCK_SPAWN_CHANCE;
	const static int BONUS_BLOCK_SPAWN_CHANCE;

public:
	Field(const sf::Vector2f& top,const sf::Vector2u& size,
		const sf::Vector2f& window_size, const sf::Vector2f& block_size);
	sf::Vector2u GetSize() const { return _size; };
	void Draw(std::shared_ptr<sf::RenderWindow> window);
	void MoveMovingBlocks();
	void AddMovingBlock();
	void ReduceHealth(unsigned pos);
	// check if x,y is free for spawning new moving block
	bool CheckXForNewMoving(float x, float y);
	void CheckCollisionsBetweenBlocks();
	std::vector<std::shared_ptr<Block>> GetGrid() { return _grid; };
	bool CheckGameEnd() const;

};

