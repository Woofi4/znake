#include "../../include/obj/drawable_block.hpp"


drawable_block::drawable_block(float x, float y, float size, const sf::Texture& texture):
	block(x, y, size), _shape({size, size}) {
	
	_shape.setPosition(x, y);
	_shape.setFillColor(sf::Color::Red);
	_shape.setTexture(&texture);
}

void drawable_block::setTexture(const sf::Texture& texture) { _shape.setTexture(&texture); }

const sf::RectangleShape& drawable_block::getShape() const { return _shape; }