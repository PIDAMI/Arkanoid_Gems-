#include "BonusedBlock.h"


using namespace sf;

std::shared_ptr<Bonus> BonusedBlock::GenerateRandomBonus() {

	int chance = rand() % 100;

	return std::make_shared<Bonus>(new BarChangeBonus());


}
