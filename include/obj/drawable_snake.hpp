#ifndef DRAWABLE_SNAKE_HPP
#define DRAWABLE_SNAKE_HPP

#include "drawable_block.hpp"

#include "vector"


namespace snake {
	extern float blockSize;
	extern unsigned defaultSize;
	extern unsigned maxSpeed;
	extern std::unordered_map<std::string, std::pair<float, float>> directions;

	bool load();
};

class drawable_snake {
	std::vector<drawable_block> _snake;
	std::pair<float, float> _direction;

public:
	drawable_snake(const drawable_block& origin, const std::pair<float, float>& direction = snake::directions["EAST"], unsigned size = snake::defaultSize);
	void add();
	void move(std::string direction);
	float getHeadX() const;
	float getHeadY() const;
	const std::vector<drawable_block>& getSnake() const;
	bool hit(const block& block) const;
	void setDirection(const std::pair<float, float>& direction);
	std::pair<float, float> getDirection();
};

#endif