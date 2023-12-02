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
	std::ifstream json("data/config.json");
	if (!json) { return false; }
	nlohmann::json config = nlohmann::json::parse(json);
	json.close();

	game::WINDOW::name = config["window"]["name"];
	game::WINDOW::width = config["window"]["width"];
	game::WINDOW::height = config["window"]["height"];
	game::PLAYER::name = config["player"]["name"];

	return true;
}

void game::drawGame(sf::RenderWindow& window) { };

void game::drawStartMenu(sf::RenderWindow& window) { };

void game::drawMenu(sf::RenderWindow& window) { };

void game::drawSettings(sf::RenderWindow& window) { };