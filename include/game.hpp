#ifndef GAME_HPP
#define GAME_HPP

#include "../external/nlohmann/json.hpp"
#include "assets.hpp"

#include <fstream>
#include <string>


namespace game {
	namespace PROPERTIES {

	};

	namespace WINDOW {
		extern std::string title;
		extern bool fullscreen;
		extern unsigned int width;
		extern unsigned int height;
	};

	namespace PLAYER {
		extern std::string name;
	};

	enum CONTROL {
		KEY_A = 0,
		KEY_D = 3,
		ESCAPE = 36,
		LEFT_ARROW = 71,
		RIGHT_ARROW = 72
	};


	bool load();

	void drawGame(sf::RenderWindow& window);

	void drawStartMenu(sf::RenderWindow& window);

	void drawMenu(sf::RenderWindow& window);

	void drawSettings(sf::RenderWindow& window);
};

#endif