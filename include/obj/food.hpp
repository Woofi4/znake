#ifndef FOOD_HPP
#define FOOD_HPP

#include <utility>


struct food {
	bool isActive;
	std::pair<unsigned, unsigned> position;

	food():
		isActive(false), position(0, 0) { }
};

#endif