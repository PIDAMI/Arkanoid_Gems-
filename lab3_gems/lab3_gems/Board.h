#pragma once
#include <cmath>
#include <vector>
#include <set>
#include "SFML/Graphics.hpp"


class Gem;

class Board : public sf::RectangleShape {
private:
	std::shared_ptr<sf::RenderWindow> _window;
	std::vector<std::vector<std::shared_ptr<Gem>>> _blocks;
	std::vector<std::set<int>> _forDropping;
	int _dimension; // board is square 
	int _space;
	float _blockSize;

	void SearchSequence(sf::Vector2i blockPos, std::set<int>& SeqElements);
	bool IfSequence(sf::Vector2i blockPos);
	void DropStep(std::vector<int>& forStep);
	void Dropping();
public:
	Board(int dimension, int space, float blockSize, 
		 std::shared_ptr<sf::RenderWindow> window);
	int Dimension() { return _dimension; }
	void Draw();
	void Swap(sf::Vector2i block1, sf::Vector2i block2);
	void IfDropped(std::vector<sf::Vector2i>& forCheck);
	//	~Board();
};
