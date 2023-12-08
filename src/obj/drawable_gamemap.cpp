#include "../../include/obj/drawable_gamemap.hpp"


drawable_gamemap::drawable_gamemap(const gamemap& mapObject, const std::pair<unsigned, unsigned>& windowSize):
	gamemap(mapObject),
	_position({(windowSize.first - _size.first * snake::blockSize) / 2, (windowSize.second - _size.second * snake::blockSize) / 2}),
	_blockSize(snake::blockSize),
	_snake(drawable_block(_position.x + _spawn.first * snake::blockSize, _position.y + _spawn.second * snake::blockSize, snake::blockSize)),
	_mapShape({_size.first * snake::blockSize, _size.second * snake::blockSize}),
	_wallShapes() {

	_mapShape.setPosition(_position);
	_mapShape.setFillColor(sf::Color::Black);

	for (const std::pair<unsigned, unsigned> wall : _walls) {
		_wallShapes.push_back(drawable_block(_position.x + wall.first * snake::blockSize, _position.y + wall.second * snake::blockSize, snake::blockSize));
	}
}

const drawable_snake& drawable_gamemap::getSnake() const { return _snake; };

drawable_snake& drawable_gamemap::getSnake() { return _snake; };

const sf::RectangleShape& drawable_gamemap::getMapShape() const { return _mapShape; };

const std::vector<drawable_block> drawable_gamemap::getWallShapes() const { return _wallShapes; };