#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>

#include "obj/gamemap.hpp"


namespace assets {
	namespace font {

	};

	namespace texture {
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