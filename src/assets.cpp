#include "../include/assets.hpp"


namespace assets::font {
	sf::Font arcade;
};

namespace assets::texture {
	sf::Texture background;
	sf::Texture start_button;
	sf::Texture start_button_selected;
	sf::Texture snake_skin;
	sf::Texture wall;
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