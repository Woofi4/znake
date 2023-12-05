#include "../../include/obj/snake.hpp"


snake::snake(const drawable_block& head, const std::pair<float, float>& direction, unsigned size):
	_snake({head}), _direction(direction) {

	for (unsigned i = 0; i < size; ++i) { add(); }
}

void snake::add() {
	float size = _snake[0].getSize();
	_snake.insert(
		_snake.begin(),
		drawable_block(_snake[0].getX() + size * _direction.first, _snake[0].getY() + size * _direction.second, size)
	);
}

void snake::move() {
	add();
	_snake.pop_back();
}

float snake::getHeadX() const { return _snake[0].getX(); }

float snake::getHeadY() const { return _snake[0].getY(); }

const std::vector<drawable_block>& snake::getSnake() const { return _snake; }

void snake::setDirection(const std::pair<float, float>& direction) { _direction = direction; }