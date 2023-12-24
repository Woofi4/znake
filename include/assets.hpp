#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>

#include "obj/gamemap.hpp"


namespace assets {
	namespace font {
		extern sf::Font bebas;
		extern sf::Font play;
		extern sf::Font opensans;
		extern sf::Font arcade;
	};

	namespace texture {
		extern sf::Texture background;
		extern sf::Texture start_button;
		extern sf::Texture start_button_selected;
		extern sf::Texture snake_skin;
		extern sf::Texture wall;
		extern sf::Texture mainMenuBackground;
		extern sf::Texture button;
		extern sf::Texture selectedButton;
	};

	namespace sound {

	};

	namespace map {
		extern gamemap box;
		extern gamemap tunnel;
		extern gamemap labyrinth;
	};
	

	bool load();
};

#endif