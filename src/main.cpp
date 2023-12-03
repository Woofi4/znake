#include "../include/game.hpp"


int main() {
	if (!(assets::load() && game::load())) { return -1; }

	sf::RenderWindow window(
		sf::VideoMode(game::window::size.x, game::window::size.y),
		game::window::title,
		(game::window::fullscreen ? sf::Style::Fullscreen : sf::Style::Default) & sf::Style::Close
	);
	game::drawMenu(window);

	return 0;
}