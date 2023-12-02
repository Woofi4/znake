#ifndef GAME_HPP
#define GAME_HPP

#include "assets.hpp"

#include <string>


namespace game {
	namespace PROPERTIES {

	};

	namespace WINDOW {
		extern std::string name;
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