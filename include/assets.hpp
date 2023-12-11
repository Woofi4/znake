#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>

#include "obj/gamemap.hpp"


namespace assets {
	namespace font {
		extern sf::Font arcade;
	};

	namespace texture {
		extern sf::Texture background;
		extern sf::Texture start_button;
		extern sf::Texture start_button_selected;
		extern sf::Texture snake_skin;
		extern sf::Texture wall;
	};

	namespace sound {

	};

	namespace map {
		extern gamemap box;
	};
	

	bool load();
};

#endif