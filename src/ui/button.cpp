#include "../../include/ui/button.hpp"
#include "../../include/game.hpp"


button::button(const scaled& scaled, const sf::Texture& active, sf::Text&& text):
	_scaled(scaled), _active(active), _inactive(*scaled.getSprite().getTexture()), _state(false), _text(std::move(text)) { _text.setPosition(scaled.getPosition()); _text.setCharacterSize(game::window::defaultFontSize*game::window::factors.x);}

button::button(scaled&& scaled, const sf::Texture& active, sf::Text&& text):
	_scaled(std::move(scaled)), _active(active), _inactive(*_scaled.getSprite().getTexture()), _state(false), _text(std::move(text)) { _text.setPosition(scaled.getPosition()); _text.setCharacterSize(game::window::defaultFontSize*game::window::factors.x);}

bool button::check(const sf::Vector2i& mpos) {
	const sf::Vector2f& position = _scaled.getPosition();
	const sf::Vector2u& size = _scaled.getSize(); 
	update((position.x <= mpos.x && mpos.x <= position.x + size.x) && (position.y <= mpos.y && mpos.y <= position.y + size.y));

	return _state;
}

void button::update(bool state) {
	if (_state == state) { return; }

	_scaled.setTexture(state ? _active : _inactive);
	_state = state;
}

const sf::Sprite& button::getSprite() const { return _scaled.getSprite(); }
const sf::Text& button::getText() const { return _text; }

bool button::getState() const { return _state; }