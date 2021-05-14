#include "Ball.h"
#include "Bar.h"
#include "Block.h"
using namespace sf;

const sf::Vector2f Ball::DEFAULT_BALL_SPEED = sf::Vector2f(5.f, 5.f);
const int RANDOM_REFLECT_CHANCE = 10;


Ball::Ball(float rad, const sf::Vector2f& pos,const sf::Color& col) {
	
	setRadius(rad);
	setPosition(pos);
	setFillColor(col);
	_stick_to_board = false;
	_reflects_bottom = false;
	_random_reflection = false;
	_start_coord = pos;
	_speed = DEFAULT_BALL_SPEED;
	_move_dir = { -1,-1 };
}


Vector2f Ball::GetTopCoord() const {
	auto pos = getPosition();
	return { pos.x + getRadius(),pos.y  };
}

Vector2f Ball::GetLeftCoord() const {
	auto pos = getPosition();
	return { pos.x ,pos.y + getRadius() };
}

Vector2f Ball::GetRightCoord() const {
	auto pos = getPosition();
	auto rad = getRadius();
	return { pos.x + 2 * rad, pos.y +  rad};
}


Vector2f Ball::GetBottomCoord() const {
	auto pos = getPosition();
	auto rad = getRadius();
	return { pos.x + rad,pos.y + 2 * rad};
}



void Ball::Move(int window_width) {
	if (_stick_to_board)
		MoveWithBar(window_width);
	else {
		if (_random_reflection)
			RandomlyReflect();

		move({ _move_dir.x * _speed.x, _move_dir.y * _speed.y });
	}
	
}

void Ball::RandomlyReflect() {
	if (rand() % 100 < RANDOM_REFLECT_CHANCE) {
		if (rand() % 2) 
			_move_dir.y *= -1;
		else	
			_move_dir.x *= -1;

		_random_reflection = false;
	}
}


void Ball::ReflectBar(const Bar& bar) {
	auto ball_pos = getPosition();
	auto rad = getRadius();
	auto bar_pos = bar.GetCoord();

	bool y_lower_bars_top = abs(ball_pos.y + 2 * rad - bar_pos.y) < _speed.y;
	bool x_to_right_from_bar_left = ball_pos.x >= bar_pos.x;
	bool x_to_left_from_bar_right = ball_pos.x <= bar_pos.x + bar.GetSize().x;

	if (y_lower_bars_top && x_to_right_from_bar_left && x_to_left_from_bar_right) {
		_move_dir.y *= -1;
		if (bar.IsBallStick()) { // bar picks up bonus, it knows if ball's stick earlier
			_stick_to_board = true;
			setPosition(ball_pos.x, _start_coord.y);
		}
	}


}




void Ball::MoveWithBar(int window_width) {
	
	auto x_coord = getPosition().x;

	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		if (x_coord >= 0)
			move({ -Bar::DEFAULT_BAR_SPEED, 0 });
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		if (x_coord + 2 * getRadius() <= window_width)
			move({ Bar::DEFAULT_BAR_SPEED, 0 });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		_stick_to_board = false;
}



void Ball::RespawnBall() {
	setPosition(_start_coord.x, _start_coord.y);
	_speed = DEFAULT_BALL_SPEED;
	_move_dir = { -1,-1 };
}


void Ball::SpeedUp(const Vector2f increment) {
	if (_speed.x > increment.x && _speed.y > increment.y ||
		increment.x > 0 && increment.y > 0) {
		
		_speed += increment;
	}

}

bool Ball::ReflectFromBlock(const Block& block) {
	bool hit = false;
	auto ball_pos = getPosition();
	auto block_pos = block.getPosition();
	auto health = block.GetHealth();
	auto radius = getRadius();
	auto block_size = block.getSize();

	float max_dist = sqrt(_speed.y * _speed.y + _speed.x * _speed.x);

	bool y_more_blocks_bot = fabs(ball_pos.y - (block_pos.y + health)) < max_dist;
	bool y_less_blocks_top = fabs(ball_pos.y + 2 * radius - block_pos.y) < max_dist;
	bool x_more_blocks_left = fabs(ball_pos.x + 2 * radius - block_pos.x) < max_dist;
	bool x_less_blocks_right = fabs(ball_pos.x - (block_pos.x + block_size.x)) < max_dist;

	bool y_more_blocks_bot_strict = ball_pos.y > block_pos.y;
	bool y_less_blocks_top_strict = ball_pos.y < block_pos.y + block_size.y;
	bool x_more_blocks_left_strict = ball_pos.x > block_pos.x;
	bool x_less_blocks_right_strict = ball_pos.x < block_pos.x + block_size.x;


	if (x_less_blocks_right && y_more_blocks_bot) {
		_move_dir.x *= -1;
		_move_dir.y *= -1;
		hit = true;
	}


	else if (x_less_blocks_right && y_less_blocks_top) {
		_move_dir.x *= -1;
		_move_dir.y *= -1;
		hit = true;
	}

	else if (x_more_blocks_left && y_less_blocks_top) {
		_move_dir.x *= -1;
		_move_dir.y *= -1;
		hit = true;
	}

	else if (x_more_blocks_left && y_more_blocks_bot) {
		_move_dir.x *= -1;
		_move_dir.y *= -1;
		hit = true;
	}

	else if (y_more_blocks_bot && x_more_blocks_left_strict && 
			 x_less_blocks_right_strict) {
		_move_dir.y *= -1;
		hit = true;
	}

	else if (y_less_blocks_top && x_more_blocks_left_strict && 
			 x_less_blocks_right_strict) {
		_move_dir.y *= -1;
		hit = true;
	}

	else if (x_more_blocks_left && y_more_blocks_bot_strict && 
			 y_less_blocks_top_strict) {
		_move_dir.x *= -1;
		hit = true;
	}

	else if (x_less_blocks_right && y_more_blocks_bot_strict &&
			 y_less_blocks_top_strict) {
		_move_dir.x *= -1;
		hit = true;
	}

	return hit;
}



void Ball::ReflectWall(int window_width) {
	auto pos = getPosition();
	
	float max_dist = sqrt(_speed.y * _speed.y + _speed.x * _speed.x);
	bool fell_left = getPosition().x <= max_dist;
	bool fell_right = fabs(pos.x + 2 * getRadius() - max_dist) >= window_width;
	bool fell_Top = pos.y <= max_dist;
	bool fell_bot = fabs(pos.y - window_width) <= max_dist;

	if (fell_left || fell_right)
		_move_dir.x *= -1;
	if (fell_Top)
		_move_dir.y *= -1;
	if (_reflects_bottom && fell_bot) {
		_move_dir.y *= -1;
		move({ 0, -_speed.y });
		_reflects_bottom = false;
		//setFillColor(sf::Color::White);
	}
}