#include "../include/game.hpp"


namespace game::window {
	std::string title;
	bool fullscreen;
	std::pair<unsigned, unsigned> size;
	std::pair<float, float> factors;
}

namespace game::player {
	std::string name;
}


bool game::load() {
	std::ifstream json("data/config.json");
	if (!json) { return false; }
	nlohmann::json config = nlohmann::json::parse(json);
	json.close();

	window::title = config["window"]["title"];
	window::fullscreen = config["window"]["fullscreen"];
	window::size = config["window"]["size"];
	window::factors = {
		window::size.first / (float) config["window"]["default_size"][0],
		window::size.second / (float) config["window"]["default_size"][1]
	};

	player::name = config["player"]["name"];

	return true;
}

#include <iostream>
void game::drawGame(sf::RenderWindow& window) {
	drawable_gamemap map(assets::map::box, window::size);
	drawable_snake& snake = map.getSnake();

	unsigned tick = 0;
	std::string direction = "EAST";
	bool isAlive = true;
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

				snake.setDirection(snake::directions[direction]);

				if (!isAlive) { }
			}
		}

		if (isAlive) {
			window.clear();
			window.draw(map.getMapShape());
			for (const drawable_block& block : map.getWallShapes()) { window.draw(block.getShape()); }
			for (const drawable_block& block : snake.getSnake()) { window.draw(block.getShape()); }
			window.display();

			if ((tick % (snake::maxSpeed - properties::speed) == 0)) { snake.move(); }
			for (const drawable_block& block : map.getWallShapes()) { if (snake.hit(block)) { isAlive = false; }}
			for (const drawable_block& block : snake.getSnake()) { if (!(snake.getHeadX() == block.getX() && snake.getHeadY() == block.getY()) && snake.hit(block)) { isAlive = false; } }

			if (++tick == window::framerate) { tick = 0; }
		}
		else { }
	}
};

void game::drawStartMenu(sf::RenderWindow& window) { };

void game::drawMenu(sf::RenderWindow& window) { };

void game::drawSettings(sf::RenderWindow& window) { };