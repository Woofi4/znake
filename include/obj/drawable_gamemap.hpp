#ifndef DRAWABLE_GAMEMAP_HPP
#define DRAWABLE_GAMEMAP_HPP

#include "gamemap.hpp"
#include "drawable_snake.hpp"
#include "../assets.hpp"


class drawable_gamemap : public gamemap {
	sf::Vector2f _position;
	float _blockSize;
	drawable_snake _snake;
	sf::RectangleShape _mapShape;
	std::vector<drawable_block> _wallShapes;

public:
	drawable_gamemap(const gamemap& mapObject, const std::pair<unsigned, unsigned>& windowSize);
	const drawable_snake& getSnake() const;
	drawable_snake& getSnake();
	const sf::RectangleShape& getMapShape() const;
	const std::vector<drawable_block> getWallShapes() const;
};

#endif