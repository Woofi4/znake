#include "../../include/ui/option.hpp"
#include "../../include/assets.hpp"


option::option(const scaled& scaled, const sf::Texture& active, const std::vector<std::string>& values):
	_values(std::move(values)), button(scaled, active, sf::Text(values[0], assets::font::bebas)), _index(0) { }

option::option(scaled&& scaled, const sf::Texture& active, const std::vector<std::string>& values):
	_values(std::move(values)), button(std::move(scaled), active, sf::Text(values[0], assets::font::bebas)), _index(0) { }

option::option(const scaled& scaled, const sf::Texture& active, std::vector<std::string>&& values):
	_values(std::move(values)), button(scaled, active, sf::Text(values[0], assets::font::bebas)), _index(0) { }

option::option(scaled&& scaled, const sf::Texture& active, std::vector<std::string>&& values):
	_values(std::move(values)), button(std::move(scaled), active, sf::Text(values[0], assets::font::bebas)), _index(0) { }

void option::next() { _index = (++_index) % _values.size(); _text.setString(_values[_index]); _text.setPosition(_scaled.getPosition());}

void option::prev() { _index = (--_index + _values.size()) % _values.size(); _text.setString(_values[_index]); _text.setPosition(_scaled.getPosition());}

const sf::Text& option::getText() const {return _text;}

const std::string& option::getValue() const { return _values[_index]; }