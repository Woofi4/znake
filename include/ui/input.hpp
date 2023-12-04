#ifndef INPUT_HPP
#define INPUT_HPP

#include "scaled.hpp"
#include "button.hpp"
#include <string>


class input: public button {
	std::vector<std::string> _values;
	int _currentValue;

public:
	input(const scaled&, const sf::Texture&, const std::vector<std::string>&);
	input(scaled&&, const sf::Texture&, const std::vector<std::string>&);
	input(const scaled& scaled, const sf::Texture& active, std::vector<std::string>&& values);
	input(scaled&& scaled, const sf::Texture& active, std::vector<std::string>&& values);
	void next();
	void prev();
	std::string getValue() const;
};

#endif
