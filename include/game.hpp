#ifndef GAME_HPP
#define GAME_HPP

#include "../external/nlohmann/json.hpp"
#include "obj/drawable_gamemap.hpp"
#include "../include/ui/button.hpp"
#include "assets.hpp"

#include <fstream>
#include <string>


namespace game {
	namespace properties {
		const unsigned speed = 0;
		const bool reverseControl = false;
		const bool has2p = false;
		const bool hasBot = false;
		const int roundsCount = 3;
	};

	namespace window {
		extern std::string title;
		extern bool fullscreen;
		extern std::pair<unsigned, unsigned> size;
		extern std::pair<float, float> factors;

		const unsigned framerate = 30;
		const float blockSize = 32;
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