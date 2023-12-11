#include "../../include/obj/drawable_gamemap.hpp"


drawable_gamemap::drawable_gamemap(const gamemap& mapObject, const std::pair<unsigned, unsigned>& windowSize):
	gamemap(mapObject),
	_position({(windowSize.first - _size.first * snake::blockSize) / 2, (windowSize.second - _size.second * snake::blockSize) / 2}),
	_blockSize(snake::blockSize),
	_snake(drawable_block(_position.x + _spawn.first * snake::blockSize, _position.y + _spawn.second * snake::blockSize, snake::blockSize, assets::texture::snake_skin)),
	_mapShape({_size.first * snake::blockSize, _size.second * snake::blockSize}),
	_wallShapes(),
	_common(),
	_booster(),
	_commonShape({snake::blockSize, snake::blockSize}),
	_boosterShape({snake::blockSize, snake::blockSize}) {

	_commonShape.setFillColor(sf::Color::Green);

	_mapShape.setPosition(_position);
	_mapShape.setFillColor(sf::Color::Black);

	for (const std::pair<unsigned, unsigned> wall : _walls) {
		_wallShapes.push_back(drawable_block(_position.x + wall.first * snake::blockSize, _position.y + wall.second * snake::blockSize, snake::blockSize, assets::texture::wall));
	}
}

const drawable_snake& drawable_gamemap::getSnake() const { return _snake; };

drawable_snake& drawable_gamemap::getSnake() { return _snake; };

const sf::RectangleShape& drawable_gamemap::getMapShape() const { return _mapShape; };

const std::vector<drawable_block> drawable_gamemap::getWallShapes() const { return _wallShapes; };

void drawable_gamemap::update() {
	if (!_common.isActive) {
		unsigned randX = rand() % _size.first;
		unsigned randY = rand() % _size.second;
		for (std::pair<unsigned, unsigned> wall : _walls) {
			while (randX == wall.first && randY == wall.second) { randX = rand() % _size.first; randY = rand() % _size.second; }
		}

		_common.position = {randX, randY};
		_common.isActive = true;
		_commonShape.setPosition({_position.x + _common.position.first * snake::blockSize, _position.y + _common.position.second * snake::blockSize});
	}
	
	if (_snake.getHeadX() == _commonShape.getPosition().x && _snake.getHeadY() == _commonShape.getPosition().y) {
		_common.isActive = false;
		_snake.add();
	}
}

const sf::RectangleShape& drawable_gamemap::getCommonShape() const { return _commonShape; }

bool drawable_gamemap::hasBooster() const { return _booster.isActive; }

const sf::RectangleShape& drawable_gamemap::getBoosterShape() const { return _boosterShape; }