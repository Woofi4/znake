#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>


namespace assets {
	namespace font {

	};

	namespace texture {
		extern sf::Texture mainMenuBackground;
		extern sf::Texture button;
		extern sf::Texture selectedButton;
	};

	namespace sound {

	};
	

	bool load();
};

#endif