#include "../../include/ui/scaled.hpp"


scaled::scaled(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& factors):
	_sprite(texture),_size(texture.getSize()) {
	

	_sprite.setPosition(position);
	setScale(factors);
}

scaled::scaled(const scaled& other):
	_sprite(other._sprite), _size(other._size) { }

scaled::scaled(scaled&& other):
	_sprite(std::move(other._sprite)), _size(std::move(other._size)) { }

void scaled::setScale(const sf::Vector2f& factors) {
	_sprite.setScale(factors);
	_size.x *= factors.x;
	_size.y *= factors.y;

	sf::Vector2f position = _sprite.getPosition();
	position.x *= factors.x;
	position.y *= factors.y;
	_sprite.setPosition(position);
}

void scaled::setTexture(const sf::Texture& texture) {
	_sprite.setTexture(texture);
}

const sf::Vector2f& scaled::getPosition() const { return _sprite.getPosition(); }

const sf::Vector2u& scaled::getSize() const { return _size; }

const sf::Sprite& scaled::getSprite() const { return _sprite; }

