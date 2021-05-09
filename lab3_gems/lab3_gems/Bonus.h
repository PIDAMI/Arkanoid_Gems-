#pragma once
#include "Board.h"

#define BONUS_CHANCE 10
#define BOMB_TARGETS 5
#define PAINT_TARGETS 3
#define COMBO_SIZE_BONUS 4




class Bonus: public sf::Sprite {
protected:
	int _num_affected_gems;
public:
	Bonus(sf::Texture& texture, sf::Vector2f pos):_num_affected_gems(0) {
		setPosition(pos);
		setTexture(texture);
	};
	Bonus(sf::Texture& texture, sf::Vector2f pos,int affected_gems_count) :
		_num_affected_gems(affected_gems_count) {
		setPosition(pos);
		setTexture(texture);

	};
	int GetNumTargets() const { return _num_affected_gems; };
	virtual std::vector<sf::Vector2i> Activate(const sf::Vector2i& board_size,
		const sf::Vector2i& coord) = 0;
	virtual ~Bonus() {};
};


class Bomb : public Bonus {
	static sf::Texture texture;
public:
	Bomb(sf::Vector2f pos) :Bonus(texture,pos,BOMB_TARGETS) {};
	virtual std::vector<sf::Vector2i> Activate(const sf::Vector2i& board_size,
										const sf::Vector2i& coord);
	static bool LoadTexture() { return texture.loadFromFile("bomb_sprite.png"); }
};


class Paint : public Bonus {
	static sf::Texture texture;
public:
	Paint(sf::Vector2f pos) :Bonus(texture,pos,PAINT_TARGETS) {};
	virtual std::vector<sf::Vector2i> Activate(const sf::Vector2i& board_size,
											const sf::Vector2i& coord);
	static bool LoadTexture() { return texture.loadFromFile("brush_sprite.png"); }
	~Paint() {};
};
