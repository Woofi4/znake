#include <iostream>
#include "../../include/ui/textinput.hpp"
#include "../../include/assets.hpp"
#include "../../include/game.hpp"


textinput::textinput(const scaled& scaled, const sf::Texture& active): button(scaled, active, sf::Text("", game::window::textinputFont))  { }

textinput::textinput(scaled&& scaled, const sf::Texture& active): button(scaled, active, sf::Text("", game::window::textinputFont)) { }

void textinput::add(char letter) {_value.append(std::string(1, letter)); _text.setString(_value);}
void textinput::remove() {if(_value.length() > 0) { _value.pop_back(); _text.setString(_value); } }

const std::string& textinput::getValue() const { return _value; }