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
	int round = game::properties::roundsCount;
	int curr = 0;

	int score1p_value = 0;
	int score2p_value = 0;
	sf::Text score1p("0", assets::font::arcade, 60);
	sf::Text score2p("0", assets::font::arcade, 60);

	while (curr != round) {
	sf::Text gameover("Game over", assets::font::arcade, 80);
	sf::Text pause("Paused", assets::font::arcade, 80);
	

	drawable_gamemap map(assets::map::labyrinth, window::size, game::properties::has2p, game::properties::hasBot);
	map.setScore1p(score1p_value);
	map.setScore2p(score2p_value);
	drawable_snake& snake = map.getSnake();
	drawable_snake& bot = map.getBot();
	
	gameover.setPosition((window::size.first / 2) - 180, 200);
	pause.setPosition((window::size.first / 2) - 140, 200);
	score1p.setPosition({map.getMapShape().getPosition().x, map.getMapShape().getPosition().y - 70});
	score2p.setPosition({map.getMapShape().getPosition().x + map.getMapShape().getSize().x - 60, map.getMapShape().getPosition().y - 70});


	unsigned tick = 0;
	std::string direction1p = "EAST";
	std::string direction2p = "EAST";
	bool isAlive = true;
	bool isPause = false;
	bool flag = false;
	while (window.isOpen() && !flag) {
		sf::Event event;
		
		while (window.pollEvent(event) && !flag) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					direction1p = "NORTH";
				}
				else if (event.key.code == sf::Keyboard::A) {
					direction1p = "WEST";
				}
				else if (event.key.code == sf::Keyboard::S) {
					direction1p = "SOUTH";
				}
				else if (event.key.code == sf::Keyboard::D) {
					direction1p = "EAST";
				}

				if (event.key.code == sf::Keyboard::Up) {
					direction2p = "NORTH";
				}
				else if (event.key.code == sf::Keyboard::Left) {
					direction2p = "WEST";
				}
				else if (event.key.code == sf::Keyboard::Down) {
					direction2p = "SOUTH";
				}
				else if (event.key.code == sf::Keyboard::Right) {
					direction2p = "EAST";
				}

				else if (event.key.code == sf::Keyboard::Escape) {
					isPause = !isPause;
				}

				if (!isAlive) { curr++; flag = true; }
			}
		}

		if (isAlive && !isPause) {
			window.clear();
			window.draw(map.getMapShape());
			window.draw(score1p);
			if (game::properties::has2p) {
				window.draw(score2p);
			}
			window.draw(map.getCommonShape());
			if (map.hasBooster()) {
				window.draw(map.getBoosterShape());
			}

			for (const drawable_block& block : map.getWallShapes()) { window.draw(block.getShape()); }
			for (const drawable_block& block : snake.getSnake()) { window.draw(block.getShape()); }
			if (game::properties::has2p) {
				for (const drawable_block& block : bot.getSnake()) { window.draw(block.getShape()); }
			}

			if ((tick % (snake::maxSpeed - properties::speed) == 0)) {
				snake.move(game::properties::reverseControl ? direction2p : direction1p);
				if (game::properties::has2p && !game::properties::hasBot) { bot.move(game::properties::reverseControl ? direction1p : direction2p); };
				map.update();

				score1p_value = map.getScore1p();
				score2p_value = map.getScore2p();
				score1p.setString(std::to_string(map.getScore1p()));
				score2p.setString(std::to_string(map.getScore2p()));
			}

			for (const drawable_block& block : map.getWallShapes()) { if (snake.hit(block)) { isAlive = false; }}
			if (game::properties::has2p) {
				for (const drawable_block& block : bot.getSnake()) { if (snake.hit(block)) { isAlive = false; }}
			}
			std::vector<drawable_block> snake_blocks = snake.getSnake();
			for (unsigned i = 1; i < snake_blocks.size(); ++i) { if (snake.hit(snake_blocks[i])) { isAlive = false; } }
			
			if (game::properties::has2p) {
				for (const drawable_block& block : map.getWallShapes()) { if (bot.hit(block)) { isAlive = false; }}
				for (const drawable_block& block : snake.getSnake()) { if (bot.hit(block)) { isAlive = false; }}
				std::vector<drawable_block> bot_blocks = bot.getSnake();
				for (unsigned i = 1; i < bot_blocks.size(); ++i) { if (bot.hit(bot_blocks[i])) { isAlive = false; } }
			}
			

			if (++tick == window::framerate) { tick = 0; }
		}
		else if (isPause) {
			window.draw(pause);
		}
		else if (!isAlive) {
			window.draw(gameover);
		}

		window.display();
	}
	}

	return;
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