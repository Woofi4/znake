#include "../../include/ui/textinput.hpp"
#include "../../include/assets.hpp"


textinput::textinput(const scaled& scaled, const sf::Texture& active): button(scaled, active, sf::Text("", assets::font::bebas))  { }

textinput::textinput(scaled&& scaled, const sf::Texture& active): button(scaled, active, sf::Text("", assets::font::bebas)) { }

void textinput::add(char letter) {_value.append(std::string(1, letter)); _text.setString(_value);}
void textinput::remove() {_value.pop_back(); _text.setString(_value);}

const std::string& textinput::getValue() const { return _value; }