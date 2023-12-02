#include "../include/game.hpp"


namespace game::WINDOW {
	std::string name;
	unsigned int width;
	unsigned int height;
}

namespace game::PLAYER {
	std::string name;
}


bool game::load() {
	game::WINDOW::name = "znake";
	game::WINDOW::width = 1024;
	game::WINDOW::height = 708;

	game::PLAYER::name = "Snake";

	return true;
}

void game::drawGame(sf::RenderWindow& window) { };

void game::drawStartMenu(sf::RenderWindow& window) { };

void game::drawMenu(sf::RenderWindow& window) { };

void game::drawSettings(sf::RenderWindow& window) { };