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

void game::drawGame(sf::RenderWindow& window) {
	std::string direction = "EAST";
	snake snake(drawable_block(100, 100, game::system::blockSize), system::direction.at(direction));

	unsigned tick = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W && direction != "SOUTH") {
					direction = "NORTH";
				}
				else if (event.key.code == sf::Keyboard::A && direction != "EAST") {
					direction = "WEST";
				}
				else if (event.key.code == sf::Keyboard::S && direction != "NORTH") {
					direction = "SOUTH";
				}
				else if (event.key.code == sf::Keyboard::D && direction != "WEST") {
					direction = "EAST";
				}

				snake.setDirection(game::system::direction.at(direction));
			}
		}

		window.clear();
		for (const drawable_block& block : snake.getSnake()) { window.draw(block.getShape());}
		window.display();

		if (tick % (game::system::maxSpeed - game::system::speed) == 0) { snake.move(); }
		
		++tick;
		if (tick == game::window::framerate) { tick = 0; }
	}
};

void game::drawStartMenu(sf::RenderWindow& window) { };

void game::drawMenu(sf::RenderWindow& window) { };

void game::drawSettings(sf::RenderWindow& window) { };