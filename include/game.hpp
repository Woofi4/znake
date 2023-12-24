#ifndef GAME_HPP
#define GAME_HPP

#include "../external/nlohmann/json.hpp"
#include "assets.hpp"

#include <fstream>
#include <string>


namespace game {
	namespace properties {
		const unsigned speed = 0;
		const bool reverseControl = false;
		const bool has2p = false;
		const bool hasBot = false;
	};

	namespace window {
		extern std::string title;
		extern bool fullscreen;
		extern sf::Vector2f size;
		extern sf::Vector2f factors;
		extern const int defaultFontSize;
		extern const sf::Font& textinputFont;
		extern const sf::Font& standartFont;
		const unsigned framerate = 30;
		const float blockSize = 32;
	};

	namespace player {
		extern std::string name;
	};

	enum CONTROL {
		KEY_A = 0,
		KEY_D = 3,
		ESCAPE = 36,
		ENTER = 58,
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