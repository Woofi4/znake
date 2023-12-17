#include "../include/assets.hpp"


namespace assets::font {
	sf::Font bebas;
};

namespace assets::texture {
	sf::Texture mainMenuBackground;
	sf::Texture button;
	sf::Texture selectedButton;

};

namespace assets::sound {

};


bool assets::load() {
	if (!texture::mainMenuBackground.loadFromFile("data/img/main_menu_background.png")) { return false; }
	if (!texture::button.loadFromFile("data/img/button.png")) { return false; }
	if (!texture::selectedButton.loadFromFile("data/img/selected_button.png")) { return false; }
	if (!font::bebas.loadFromFile("data/fonts/Bebas-Regular.ttf")) { return false; }

	return true;
}