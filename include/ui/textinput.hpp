#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "button.hpp"
#include "scaled.hpp"

#include <string>


class textinput : public button {
	std::string _value;

public:
	textinput(const scaled& scaled, const sf::Texture& active);
	textinput(scaled&& scaled, const sf::Texture& active);
	void add(char letter);
	void remove();
	const std::string& getValue() const;
};
#endif
