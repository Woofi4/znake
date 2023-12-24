#include "../../include/obj/block.hpp"


block::block(float x, float y, float size):
	_x(x), _y(y), _size(size) { }

void block::setX(float x) { _x = x; };

void block::setY(float y) { _y = y; };

void block::addX(float dx) { _x += dx; }

void block::addY(float dy) { _y += dy; }

float block::getX() const { return _x; }

float block::getY() const { return _y; }

float block::getCenterX() const { return _x - (_size / 2); }

float block::getCenterY() const { return _y - (_size / 2); }

float block::getSize() const { return _size; }