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
	sf::Text gameover("Game over", assets::font::arcade, 80);
	gameover.setPosition((window::size.first / 2) - 180, 200);

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
				if (event.key.code == sf::Keyboard::W) {
					direction = "NORTH";
				}
				else if (event.key.code == sf::Keyboard::A) {
					direction = "WEST";
				}
				else if (event.key.code == sf::Keyboard::S) {
					direction = "SOUTH";
				}
				else if (event.key.code == sf::Keyboard::D) {
					direction = "EAST";
				}

				if (!isAlive) { return; }
			}
		}

		if (isAlive) {
			window.clear();
			window.draw(map.getMapShape());
			window.draw(map.getCommonShape());
			for (const drawable_block& block : map.getWallShapes()) { window.draw(block.getShape()); }
			for (const drawable_block& block : snake.getSnake()) { window.draw(block.getShape()); }

			if ((tick % (snake::maxSpeed - properties::speed) == 0)) { snake.move(direction); map.update(); }
			for (const drawable_block& block : map.getWallShapes()) { if (snake.hit(block)) { isAlive = false; }}
			std::vector<drawable_block> snake_blocks = map.getSnake().getSnake();
			for (unsigned i = 1; i < snake_blocks.size(); ++i) { if (snake.hit(snake_blocks[i])) { isAlive = false; } }
			if (++tick == window::framerate) { tick = 0; }
		}
		else {
			window.draw(gameover);
		}

		window.display();
	}
};

void game::drawStartMenu(sf::RenderWindow& window) { };

void game::drawMenu(sf::RenderWindow& window) {
	scaled background(assets::texture::background, {0, 0}, {game::window::factors.first, game::window::factors.second});
	button start_button(scaled(assets::texture::start_button, {150, 200}, {game::window::factors.first, game::window::factors.second}), assets::texture::start_button_selected);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::MouseMoved) {
				start_button.check(sf::Mouse::getPosition(window));
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::S) {
					start_button.update(true);
				}
				else if (event.key.code == sf::Keyboard::W) {
					start_button.update(false);
				}
			}
			else if (start_button.getState() && (event.type == sf::Event::MouseButtonPressed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))) {
				drawGame(window);
			}
		}

		window.clear();
		window.draw(background.getSprite());
		window.draw(start_button.getSprite());
		window.display();
	}
};

void game::drawSettings(sf::RenderWindow& window) { };