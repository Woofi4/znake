#ifndef SCALED_HPP
#define SCALED_HPP

#include <SFML/Graphics.hpp>


class scaled {
	sf::Sprite _sprite;
	sf::Vector2u _size;

public:
	scaled(const sf::Texture&, const sf::Vector2f& = {0, 0}, const sf::Vector2f& = {1, 1});
	scaled(const scaled&);
	scaled(scaled&&);
	void setScale(const sf::Vector2f&);
	void setTexture(const sf::Texture&);
	const sf::Vector2f& getPosition() const;
	const sf::Vector2u& getSize() const;
	const sf::Sprite& getSprite() const;
};

#endif