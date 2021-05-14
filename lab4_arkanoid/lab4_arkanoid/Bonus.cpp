#include "Bonus.h"
#include "Bar.h"

using namespace sf;

sf::Texture BarChangeBonus::TEXTURE = sf::Texture();

void BarChangeBonus::LoadTexture() {

	BarChangeBonus::TEXTURE.loadFromFile("bar_change_bonus.png");
}



bool Bonus::IsContactedWithBar(const Bar& bar) const {

	auto bar_coord = bar.GetCoord();
	auto bar_size = bar.GetSize();
	
	auto bonus_size = _size;
	auto bonus_coord = getPosition();
	
	return (bonus_coord.y + bonus_size.y) >= bar_coord.y &&
		(bonus_coord.x + bonus_size.x >= bar_coord.x ||
		bonus_coord.x <= bar_coord.x + bar_size.x);
}
