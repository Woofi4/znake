#ifndef GAME_HPP
#define GAME_HPP

#include "../external/nlohmann/json.hpp"
#include "../include/obj/snake.hpp"
#include "assets.hpp"

#include <fstream>
#include <string>


namespace game {
	namespace properties {
		
	};

	namespace system {
		const unsigned maxSpeed = 8;
		const unsigned speed = 0;
		const float blockSize = 32;
		const std::unordered_map<std::string, std::pair<float, float>> direction = {
			{"NORTH", {0, -1}},
			{"WEST", {-1, 0}},
			{"SOUTH", {0, 1}},
			{"EAST", {1, 0}}
		};
	}

	namespace window {
		extern std::string title;
		extern bool fullscreen;
		const unsigned framerate = 120;
		extern sf::Vector2f size;
		extern sf::Vector2f factors;
	};

	namespace player {
		extern std::string name;
	};


	bool load();

	void drawGame(sf::RenderWindow& window);

	void drawStartMenu(sf::RenderWindow& window);

	void drawMenu(sf::RenderWindow& window);

	void drawSettings(sf::RenderWindow& window);
};

#endif