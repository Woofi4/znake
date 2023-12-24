#include "../../include/obj/drawable_snake.hpp"


namespace snake {
	float blockSize;
	unsigned defaultSize;
	unsigned maxSpeed;
	std::unordered_map<std::string, std::pair<float, float>> directions;
}


bool snake::load() {
	blockSize = 32;
	defaultSize = 5;
	maxSpeed = 8;
	directions = {
		{"NORTH", {0, -1}},
		{"WEST", {-1, 0}},
		{"SOUTH", {0, 1}},
		{"EAST", {1, 0}}
	};

	return true;
}

drawable_snake::drawable_snake(const drawable_block& origin, const std::pair<float, float>& direction, unsigned size):
	_snake({origin}), _direction(direction) {

	for (unsigned i = 0; i < size; ++i) { add(); }
}

void drawable_snake::add() {
	float size = _snake[0].getSize();
	_snake.insert(
		_snake.begin(),
		drawable_block(_snake[0].getX() + size * _direction.first, _snake[0].getY() + size * _direction.second, size, _snake[0].getTexture())
	);
}

void drawable_snake::move(std::string direction) {
	std::pair<float, float> dir = snake::directions[direction];
	dir.first = -dir.first;
	dir.second = -dir.second;
	if (_direction != dir) {
		_direction = snake::directions[direction];
	}
	
	add();
	_snake.pop_back();
}

float drawable_snake::getHeadX() const { return _snake[0].getX(); }

float drawable_snake::getHeadY() const { return _snake[0].getY(); }

const std::vector<drawable_block>& drawable_snake::getSnake() const { return _snake; }

bool drawable_snake::hit(const block& block) const { return _snake[0].getX() == block.getX() && _snake[0].getY() == block.getY(); }

void drawable_snake::setDirection(const std::pair<float, float>& direction) { _direction = direction; }

std::pair<float, float> drawable_snake::getDirection() { return _direction; }