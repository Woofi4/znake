#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "scaled.hpp"


class button {
protected:
	scaled _scaled;
	sf::Texture _active;
	sf::Texture _inactive;
	sf::Text _text;
	bool _state;

public:
	button(const scaled&, const sf::Texture&, sf::Text&&);
	button(scaled&&, const sf::Texture&, sf::Text&&);
	bool check(const sf::Vector2i&);
	void update(bool);
	const sf::Sprite& getSprite() const;
	const sf::Text& getText() const;
	bool getState() const;
};

#endif