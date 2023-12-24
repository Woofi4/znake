#include "../include/assets.hpp"


namespace assets::font {
	sf::Font arcade;
	sf::Font bebas;
	sf::Font play;
	sf::Font opensans;
};

namespace assets::texture {
	sf::Texture background;
	sf::Texture start_button;
	sf::Texture start_button_selected;
	sf::Texture snake_skin;
	sf::Texture wall;
	sf::Texture mainMenuBackground;
	sf::Texture button;
	sf::Texture selectedButton;

};

namespace assets::sound {

};

namespace assets::map {
	gamemap box;
};


bool assets::load() {
	if (!font::arcade.loadFromFile("data/fonts/arcadeclassic.ttf")) { return false; }
	if (!texture::background.loadFromFile("data/textures/background.png")) { return false; }
	if (!texture::start_button.loadFromFile("data/textures/start_button.png")) { return false; }
	if (!texture::start_button_selected.loadFromFile("data/textures/start_button_selected.png")) { return false; }
	if (!texture::snake_skin.loadFromFile("data/textures/snake_skin.png")) { return false; }
	if (!texture::wall.loadFromFile("data/textures/wall.png")) { return false; }

	std::ifstream stream("data/maps/box.json");
	if (!stream) { return false; }
	map::box = *gamemap::load(stream);
	stream.close();

	return true;
}
bool assets::load() {
	if (!texture::mainMenuBackground.loadFromFile("data/img/main_menu_background.png")) { return false; }
	if (!texture::button.loadFromFile("data/img/button.png")) { return false; }
	if (!texture::selectedButton.loadFromFile("data/img/selected_button.png")) { return false; }
	if (!font::bebas.loadFromFile("data/fonts/Bebas-Regular.ttf")) { return false; }
	if (!font::play.loadFromFile("data/fonts/Play-Bold.ttf")) { return false; }
	if (!font::opensans.loadFromFile("data/fonts/OpenSans-MediumItalic.ttf")) { return false; }

	return true;
}