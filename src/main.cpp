#include "../include/game.hpp"
#include "../include/obj/drawable_snake.hpp"


int main() {
	if (!(assets::load() && game::load() && snake::load())) { return -1; }

	sf::RenderWindow window(
		sf::VideoMode(game::window::size.x, game::window::size.y),
		game::window::title,
		(game::window::fullscreen ? sf::Style::Fullscreen : sf::Style::Default) & sf::Style::Close
	);
	window.setFramerateLimit(game::window::framerate);

	game::drawMenu(window);

	return 0;
}