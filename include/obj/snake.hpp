#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "drawable_block.hpp"

#include "vector"


class snake {
	std::vector<drawable_block> _snake;
	std::pair<float, float> _direction;

public:
	snake(const drawable_block& head, const std::pair<float, float>& dir, unsigned size = 3);
	void add();
	void move();
	float getHeadX() const;
	float getHeadY() const;
	const std::vector<drawable_block>& getSnake() const;
	void setDirection(const std::pair<float, float>& direction);
};

#endif