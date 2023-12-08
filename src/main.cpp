#include "../include/game.hpp"


int main() {
	if (!(assets::load() && game::load() && snake::load())) { return -1; }

	sf::RenderWindow window(
		sf::VideoMode(game::window::size.first, game::window::size.second),
		game::window::title,
		(game::window::fullscreen ? sf::Style::Fullscreen : sf::Style::Default) & sf::Style::Close
	);
	window.setFramerateLimit(game::window::framerate);

	game::drawGame(window);

	return 0;
}