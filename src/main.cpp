#include "../include/game.hpp"


int main() {
	if (!(assets::load() && game::load())) { return -1; }

	sf::RenderWindow window(sf::VideoMode(game::WINDOW::width, game::WINDOW::height), game::WINDOW::name);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::KeyPressed) { }
		}

		window.clear();
		window.display();
	}

	return 0;
}