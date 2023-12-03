#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "scaled.hpp"


class button {
	scaled _scaled;
	sf::Texture _active;
	sf::Texture _inactive;
	bool _state;

public:
	button(const scaled&, const sf::Texture&);
	button(scaled&&, const sf::Texture&);
	bool check(const sf::Vector2i&);
	void update(bool);
	const sf::Sprite& getSprite() const;
};

#endif