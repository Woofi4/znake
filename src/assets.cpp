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
	gamemap tunnel;
	gamemap labyrinth;
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

	std::ifstream stream1("data/maps/tunnel.json");
	if (!stream1) { return false; }
	map::tunnel = *gamemap::load(stream1);
	stream1.close();

	std::ifstream stream2("data/maps/labyrinth.json");
	if (!stream2) { return false; }
	map::labyrinth = *gamemap::load(stream2);
	stream2.close();

	return true;
}