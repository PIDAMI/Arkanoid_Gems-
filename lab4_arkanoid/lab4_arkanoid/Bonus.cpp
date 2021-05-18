#include "Bonus.h"
#include "Bar.h"
#include "Ball.h"
#include "Field.h"

using namespace sf;

const float Bonus::DEFAULT_BONUS_SPEED = 1.f;
const int Bonus::BONUS_SPAWN_CHANCE = 10;
const sf::Vector2u Bonus::DEFAULT_SPRITE_SIZE = Vector2u(40,40);
const float BarChangeBonus::DEFAULT_SIZE_MULTIPLIER = 1.4f;
const float BallSpeedBonus::DEFAULT_SPEED_MULTIPLIER = 1.2f;

bool Bonus::IsContactedWithBar(const Bar& bar) const {

	auto bar_coord = bar.GetCoord();
	auto bar_size = bar.GetSize();
	
	auto bonus_size = _size;
	auto bonus_coord = getPosition();
	
	return (bonus_coord.y + bonus_size.y) >= bar_coord.y &&
		(bonus_coord.x + bonus_size.x >= bar_coord.x ||
		bonus_coord.x <= bar_coord.x + bar_size.x);
}

void BarChangeBonus::Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
	std::shared_ptr<Bar> bar) {
	
	auto cur_bar_size = bar->GetSize();
	Vector2f new_bar_size = { cur_bar_size.x * _size_multiplier, cur_bar_size.y };
	bar->SetSize(new_bar_size);

}

void BallSpeedBonus::Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
	std::shared_ptr<Bar> bar){
	
	auto cur_speed = ball->GetSpeed();
	Vector2f new_speed = { cur_speed.x * _speed_multiplier,
						 cur_speed.y * _speed_multiplier };
	ball->SpeedUp(new_speed - cur_speed);

}

void BarStickBonus::Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
	std::shared_ptr<Bar> bar) {
	bar->SetBallStick(true);
	bar->SetColor(sf::Color::Magenta);
}


void BotReflectBonus::Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
	std::shared_ptr<Bar> bar) {

	ball->SetBottomReflection(true);
	ball->setFillColor(sf::Color::Magenta);
}

void ChangeTrajectoryBonus::Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
	std::shared_ptr<Bar> bar) {
	
	ball->SetRandReflection(true);


}

void MovingBlockBonus::Activate(std::shared_ptr<Field> field, std::shared_ptr<Ball> ball,
	std::shared_ptr<Bar> bar) {

	int window_width = field->GetSize().x * field->GetGrid()[0]->getSize().x;

	field->AddMovingBlock(window_width);
}