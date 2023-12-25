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
	sf::Texture back;
	sf::Texture back_selected;
	sf::Texture box_prev;
	sf::Texture tunnel_prev;
	sf::Texture labyrinth_prev;
	sf::Texture horizontal_option;
	sf::Texture horizontal_option_selected;
	sf::Texture vertical_option;
	sf::Texture vertical_option_selected;
	sf::Texture settingsBackground;
	sf::Texture startMenuBackground;
	sf::Texture textInput;
	sf::Texture textInput_selected;
	sf::Texture startbutton;
	sf::Texture startselectedButton;

};

namespace assets::sound {

};

namespace assets::map {
	gamemap box;
	gamemap tunnel;
	gamemap labyrinth;
};


bool assets::load() {
	if (!texture::back.loadFromFile("data/img/back.png")) { return false; }
	if (!texture::back_selected.loadFromFile("data/img/back_selected.png")) { return false; }
	if (!texture::box_prev.loadFromFile("data/img/map_preview/box_prev.png")) { return false; }
	if (!texture::tunnel_prev.loadFromFile("data/img/map_preview/tunnel_prev.png")) { return false; }
	if (!texture::labyrinth_prev.loadFromFile("data/img/map_preview/labyrinth_prev.png")) { return false; }
	if (!texture::horizontal_option.loadFromFile("data/img/horizontal_option.png")) { return false; }
	if (!texture::horizontal_option_selected.loadFromFile("data/img/horizontal_option_selected.png")) { return false; }
	if (!texture::vertical_option.loadFromFile("data/img/vertical_option.png")) { return false; }
	if (!texture::vertical_option_selected.loadFromFile("data/img/vertical_option_selected.png")) { return false; }
	if (!texture::textInput.loadFromFile("data/img/textinput.png")) { return false; }
	if (!texture::textInput_selected.loadFromFile("data/img/textinput_selected.png")) { return false; }
	if (!texture::startbutton.loadFromFile("data/img/startbutton.png")) { return false; }
	if (!texture::startselectedButton.loadFromFile("data/img/startselectedButton.png")) { return false; }
	if (!texture::settingsBackground.loadFromFile("data/img/settings_background.png")) { return false; }
	if (!texture::startMenuBackground.loadFromFile("data/img/start_menu_background.png")) { return false; }

	if (!font::arcade.loadFromFile("data/fonts/arcadeclassic.ttf")) { return false; }
	if (!texture::background.loadFromFile("data/textures/background.png")) { return false; }
	if (!texture::start_button.loadFromFile("data/textures/start_button.png")) { return false; }
	if (!texture::start_button_selected.loadFromFile("data/textures/start_button_selected.png")) { return false; }
	if (!texture::snake_skin.loadFromFile("data/textures/snake_skin.png")) { return false; }
	if (!texture::wall.loadFromFile("data/textures/wall.png")) { return false; }
	if (!texture::mainMenuBackground.loadFromFile("data/img/main_menu_background.png")) { return false; }
	if (!texture::button.loadFromFile("data/img/button.png")) { return false; }
	if (!texture::selectedButton.loadFromFile("data/img/selected_button.png")) { return false; }
	if (!font::bebas.loadFromFile("data/fonts/Bebas-Regular.ttf")) { return false; }
	if (!font::play.loadFromFile("data/fonts/Play-Bold.ttf")) { return false; }
	if (!font::opensans.loadFromFile("data/fonts/OpenSans-MediumItalic.ttf")) { return false; }


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