#ifndef OPTION_HPP
#define OPTION_HPP

#include "button.hpp"

#include <string>


class option : public button {
	std::vector<std::string> _values;
	int _index;

public:
	option(const scaled&, const sf::Texture&, const std::vector<std::string>&);
	option(scaled&&, const sf::Texture&, const std::vector<std::string>&);
	option(const scaled& scaled, const sf::Texture& active, std::vector<std::string>&& values);
	option(scaled&& scaled, const sf::Texture& active, std::vector<std::string>&& values);
	void next();
	void prev();
	const std::string& getValue() const;
};

#endif