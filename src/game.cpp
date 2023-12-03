#include "../include/game.hpp"


namespace game::window {
	std::string title;
	bool fullscreen;
	sf::Vector2f size;
	sf::Vector2f factors;
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
	game::window::size = { 
		config["window"]["width"],
		config["window"]["height"]
	};
	game::window::factors = {
		game::window::size.x / (float) config["window"]["default_width"],
		game::window::size.y / (float) config["window"]["default_height"]
	};

	game::player::name = config["player"]["name"];

	return true;
}

void game::drawGame(sf::RenderWindow& window) { };

void game::drawStartMenu(sf::RenderWindow& window) { };

void game::drawMenu(sf::RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
		}

		window.clear();
		window.display();
	}
};

void game::drawSettings(sf::RenderWindow& window) { };