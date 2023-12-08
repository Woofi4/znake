#ifndef DRAWABLE_BLOCK_HPP
#define DRAWABLE_BLOCK_HPP

#include "block.hpp"

#include <SFML/Graphics.hpp>


class drawable_block : public block {
	sf::RectangleShape _shape;

public:
	drawable_block(float x, float y, float size, const sf::Texture& texture = {});
	void setTexture(const sf::Texture& texture);
	const sf::RectangleShape& getShape() const;
	const sf::Texture& getTexture() const;
};

#endif