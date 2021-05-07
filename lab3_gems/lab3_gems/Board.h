#pragma once
#include <cmath>
#include <vector>
#include <set>
#include "SFML/Graphics.hpp"


class Gem;

class Board : public sf::IntRect {
private:
	std::shared_ptr<sf::RenderWindow> _window;
	std::vector<std::vector<std::shared_ptr<Gem>>> _blocks;
	std::vector<std::set<int>> _forDropping;
	int _dimension; // board is square 
	int _space;
	float _block_size;

	void SearchSequence(sf::Vector2i block_pos, std::set<int>& seq_elems);
	bool IfSequence(sf::Vector2i block_pos);
	void DropStep(std::vector<int>& forStep);
	void Dropping();
public:
	Board(int dimension, int space, float block_size, 
		 std::shared_ptr<sf::RenderWindow> window);
	int Dimension() { return _dimension; }
	void Draw();
	void Swap(sf::Vector2i block1, sf::Vector2i block2);
	void IfDropped(std::vector<sf::Vector2i>& for_check);
	//	~Board();
};
