#include "../../include/ui/input.hpp"


input::input(const scaled& scaled, const sf::Texture& active, const std::vector<std::string>& values):
		button(scaled, active), _values(values), _currentValue(0) { }

input::input(scaled&& scaled, const sf::Texture& active, const std::vector<std::string>& values):
		button(std::move(scaled), active), _values(values), _currentValue(0) { }

input::input(const scaled& scaled, const sf::Texture& active, std::vector<std::string>&& values):
		button(scaled, active), _values(std::move(values)), _currentValue(0) { }

input::input(scaled&& scaled, const sf::Texture& active, std::vector<std::string>&& values):
		button(std::move(scaled), active), _values(std::move(values)), _currentValue(0) { }

void input::next(){ _currentValue = (++_currentValue)%_values.size(); }

void input::prev(){ _currentValue = (--_currentValue)%_values.size(); }

std::string input::getValue() const { return _values[_currentValue]; }