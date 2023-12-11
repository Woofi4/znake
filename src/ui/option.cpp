#include "../../include/ui/option.hpp"


option::option(const scaled& scaled, const sf::Texture& active, const std::vector<std::string>& values):
	button(scaled, active), _values(values), _index(0) { }

option::option(scaled&& scaled, const sf::Texture& active, const std::vector<std::string>& values):
	button(std::move(scaled), active), _values(values), _index(0) { }

option::option(const scaled& scaled, const sf::Texture& active, std::vector<std::string>&& values):
	button(scaled, active), _values(std::move(values)), _index(0) { }

option::option(scaled&& scaled, const sf::Texture& active, std::vector<std::string>&& values):
	button(std::move(scaled), active), _values(std::move(values)), _index(0) { }

void option::next() { _index = (++_index) % _values.size(); }

void option::prev() { _index = (--_index) % _values.size(); }

const std::string& option::getValue() const { return _values[_index]; }