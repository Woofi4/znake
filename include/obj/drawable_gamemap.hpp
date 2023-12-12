#ifndef DRAWABLE_GAMEMAP_HPP
#define DRAWABLE_GAMEMAP_HPP

#include "gamemap.hpp"
#include "drawable_snake.hpp"
#include "food.hpp"
#include "../assets.hpp"


class drawable_gamemap : public gamemap {
	sf::Vector2f _position;
	float _blockSize;
	drawable_snake _snake;
	drawable_snake _bot;
	sf::RectangleShape _mapShape;
	std::vector<drawable_block> _wallShapes;
	food _common;
	food _booster;
	sf::RectangleShape _commonShape;
	sf::RectangleShape _boosterShape;
	sf::Clock _timer;
	unsigned _score1p;
	unsigned _score2p;
	bool _has2p;
	bool _hasBot;

public:
	drawable_gamemap(const gamemap& mapObject, const std::pair<unsigned, unsigned>& windowSize, bool has2p, bool hasBot);
	const drawable_snake& getSnake() const;
	drawable_snake& getSnake();
	const drawable_snake& getBot() const;
	drawable_snake& getBot();
	const sf::RectangleShape& getMapShape() const;
	const std::vector<drawable_block> getWallShapes() const;

	void update();
	const sf::RectangleShape& getCommonShape() const;
	bool hasBooster() const;
	const sf::RectangleShape& getBoosterShape() const;
	unsigned getScore1p() const;
	unsigned getScore2p() const;
};

#endif