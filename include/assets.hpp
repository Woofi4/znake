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
		extern sf::Texture snake_skin;
		extern sf::Texture snake_skin_red;
		extern sf::Texture wall;
		extern sf::Texture mainMenuBackground;
		extern sf::Texture button;
		extern sf::Texture selectedButton;
		extern sf::Texture back;
		extern sf::Texture back_selected;
		extern sf::Texture box_prev;
		extern sf::Texture tunnel_prev;
		extern sf::Texture labyrinth_prev;
		extern sf::Texture horizontal_option;
		extern sf::Texture horizontal_option_selected;
		extern sf::Texture vertical_option;
		extern sf::Texture vertical_option_selected;
		extern sf::Texture settingsBackground;
		extern sf::Texture startMenuBackground;
		extern sf::Texture textInput;
		extern sf::Texture textInput_selected;
		extern sf::Texture startbutton;
		extern sf::Texture startselectedButton;
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