#pragma once
#include <cmath>
#include <vector>
#include <set>
#include "SFML/Graphics.hpp"

#define DROP_THRESHOLD 3
class Gem;

class Board : public sf::IntRect {

private:
	
	std::vector<std::vector<std::shared_ptr<Gem>>> _gems;
	sf::RenderWindow* _window;

	std::vector<std::set<int>> _for_dropping;
	int _dimension; // board is square 
	int _space;
	float _block_size;

	void SearchSequence(sf::Vector2i block_pos, std::set<int>& seq_elems);
	bool IfSequence(sf::Vector2i block_pos);
	void DropStep(std::vector<int>& forStep);
	void Dropping();
	bool IsColorMatch(const sf::Vector2i& gem_pos, const sf::Vector2i& neighbor) const;
public:
	Board(int dimension, int space, float block_size, sf::RenderWindow* window);
	int GetDimension() { return _dimension; }
	void Draw();
	void Swap(sf::Vector2i block1, sf::Vector2i block2);
	void IfDropped(std::vector<sf::Vector2i>& for_check);
};
