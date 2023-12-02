#include "../include/game.hpp"


namespace game::WINDOW {
	std::string title;
	bool fullscreen;
	unsigned int width;
	unsigned int height;
	float wscale;
	float hscale;
}

namespace game::PLAYER {
	std::string name;
}


bool game::load() {
	std::ifstream json("data/config.json");
	if (!json) { return false; }
	
	nlohmann::json config = nlohmann::json::parse(json);
	json.close();

	game::WINDOW::title = config["window"]["name"];

	game::WINDOW::fullscreen = config["window"]["fullscreen"];
	game::WINDOW::width = config["window"]["width"];
	game::WINDOW::height = config["window"]["height"];
	game::WINDOW::wscale = game::WINDOW::width / (float) config["window"]["default_width"];
	game::WINDOW::hscale = game::WINDOW::height / (float) config["window"]["default_height"];

	game::PLAYER::name = config["player"]["name"];

	return true;
}

void game::drawGame(sf::RenderWindow& window) { };

void game::drawStartMenu(sf::RenderWindow& window) { };

void game::drawMenu(sf::RenderWindow& window) { };

void game::drawSettings(sf::RenderWindow& window) { };