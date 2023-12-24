#include "../../include/obj/drawable_gamemap.hpp"


drawable_gamemap::drawable_gamemap(const gamemap& mapObject, const std::pair<unsigned, unsigned>& windowSize, bool has2p, bool hasBot):
	gamemap(mapObject),
	_position({(windowSize.first - _size.first * snake::blockSize) / 2, (windowSize.second - _size.second * snake::blockSize) / 2}),
	_blockSize(snake::blockSize),
	_snake(drawable_block(_position.x + _spawn1p.first * snake::blockSize, _position.y + _spawn1p.second * snake::blockSize, snake::blockSize, assets::texture::snake_skin)),
	_bot(drawable_block(_position.x + _spawn2p.first * snake::blockSize, _position.y + _spawn2p.second * snake::blockSize, snake::blockSize, assets::texture::snake_skin)),
	_mapShape({_size.first * snake::blockSize, _size.second * snake::blockSize}),
	_wallShapes(),
	_common(),
	_booster(),
	_commonShape({snake::blockSize, snake::blockSize}),
	_boosterShape({snake::blockSize, snake::blockSize}),
	_timer(),
	_score1p(0),
	_score2p(0),
	_has2p(has2p),
	_hasBot(hasBot) {

	_commonShape.setFillColor(sf::Color::Green);
	_boosterShape.setFillColor(sf::Color::Blue);

	_mapShape.setPosition(_position);
	_mapShape.setFillColor(sf::Color::Black);

	for (const std::pair<unsigned, unsigned> wall : _walls) {
		_wallShapes.push_back(drawable_block(_position.x + wall.first * snake::blockSize, _position.y + wall.second * snake::blockSize, snake::blockSize, assets::texture::wall));
	}
}

const drawable_snake& drawable_gamemap::getSnake() const { return _snake; };

drawable_snake& drawable_gamemap::getSnake() { return _snake; };

const drawable_snake& drawable_gamemap::getBot() const { return _bot; };

drawable_snake& drawable_gamemap::getBot() { return _bot; };

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

	if (_common.isActive && _snake.getHeadX() == _commonShape.getPosition().x && _snake.getHeadY() == _commonShape.getPosition().y) {
		_common.isActive = false;
		_snake.add();
		_score1p += 20;
	}
	else if (_has2p && _common.isActive && _bot.getHeadX() == _commonShape.getPosition().x && _bot.getHeadY() == _commonShape.getPosition().y) {
		_common.isActive = false;
		_bot.add();
		_score2p += 20;
	}

	if (!_booster.isActive && _timer.getElapsedTime().asSeconds() >= 15) {
		unsigned randX = rand() % _size.first;
		unsigned randY = rand() % _size.second;
		for (std::pair<unsigned, unsigned> wall : _walls) {
			while (randX == wall.first && randY == wall.second) { randX = rand() % _size.first; randY = rand() % _size.second; }
		}

		_booster.position = {randX, randY};
		_booster.isActive = true;
		_boosterShape.setPosition({_position.x + _booster.position.first * snake::blockSize, _position.y + _booster.position.second * snake::blockSize});
		_timer.restart();
	}
	else if (_booster.isActive && _timer.getElapsedTime().asSeconds() >= 5) {
		_booster.isActive = false;
		_timer.restart();
	}

	if (_booster.isActive && _snake.getHeadX() == _boosterShape.getPosition().x && _snake.getHeadY() == _boosterShape.getPosition().y) {
		_booster.isActive = false;
		_timer.restart();
		_snake.add();
		_score1p += (5 - _timer.getElapsedTime().asSeconds()) * 20;
	}
	else if (_has2p && _booster.isActive && _bot.getHeadX() == _boosterShape.getPosition().x && _bot.getHeadY() == _boosterShape.getPosition().y) {
		_booster.isActive = false;
		_timer.restart();
		_bot.add();
		_score2p += (5 - _timer.getElapsedTime().asSeconds()) * 20;
	}

	// Bot logic
	if (_has2p && _hasBot) {
		//_bot.move();
	}
}

const sf::RectangleShape& drawable_gamemap::getCommonShape() const { return _commonShape; }

bool drawable_gamemap::hasBooster() const { return _booster.isActive; }

const sf::RectangleShape& drawable_gamemap::getBoosterShape() const { return _boosterShape; }

unsigned drawable_gamemap::getScore1p() const {
	return _score1p;
}

unsigned drawable_gamemap::getScore2p() const {
	return _score2p;
}

void drawable_gamemap::setScore1p(unsigned score) {
	_score1p = score;
}

void drawable_gamemap::setScore2p(unsigned score) {
	_score2p = score;;
}