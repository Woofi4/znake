#include "../include/game.hpp"


namespace game::window {
	std::string title;
	bool fullscreen;
	unsigned int width;
	unsigned int height;
	float wscale;
	float hscale;
}

namespace game::player {
	std::string name;
}


bool game::load() {
	std::ifstream json("data/config.json");
	if (!json) { return false; }

	nlohmann::json config = nlohmann::json::parse(json);
	json.close();

	game::window::title = config["window"]["title"];

	game::window::fullscreen = config["window"]["fullscreen"];
	game::window::width = config["window"]["width"];
	game::window::height = config["window"]["height"];
	game::window::wscale = game::window::width / (float) config["window"]["default_width"];
	game::window::hscale = game::window::height / (float) config["window"]["default_height"];

	game::player::name = config["player"]["name"];

	return true;
}

void game::drawGame(sf::RenderWindow& window) { };

void game::drawStartMenu(sf::RenderWindow& window) { };

void game::drawMenu(sf::RenderWindow& window) { };

void game::drawSettings(sf::RenderWindow& window) { };