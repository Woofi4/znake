#include "../include/assets.hpp"


namespace assets::font {

};

namespace assets::texture {
	sf::Texture snake_skin;
	sf::Texture wall;
};

namespace assets::sound {

};

namespace assets::map {
	gamemap box;
};


bool assets::load() {
	if (!texture::snake_skin.loadFromFile("data/textures/snake_skin.png")) { return false; }
	if (!texture::wall.loadFromFile("data/textures/wall.png")) { return false; }

	std::ifstream stream("data/maps/box.json");
	if (!stream) { return false; }
	map::box = *gamemap::load(stream);
	stream.close();

	return true;
}