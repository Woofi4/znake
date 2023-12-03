#include <iostream>
#include <vector>
#include "../include/game.hpp"
#include "../include/ui/button.hpp"


namespace game::window {
	std::string title;
	bool fullscreen;
	sf::Vector2f size;
	sf::Vector2f factors;
}

namespace game::player {
	std::string name;
}


bool game::load() {
	std::ifstream json("data/config.json");
	if (!json) { return false; }

	nlohmann::json config = nlohmann::json::parse(json);
	json.close();

	game::window::title = config["window"]["title"];

	game::window::fullscreen = config["window"]["fullscreen"];
	game::window::size = { 
		config["window"]["width"],
		config["window"]["height"]
	};
	game::window::factors = {
		game::window::size.x / (float) config["window"]["default_width"],
		game::window::size.y / (float) config["window"]["default_height"]
	};

	game::player::name = config["player"]["name"];

	return true;
}

void game::drawGame(sf::RenderWindow& window) { };

void game::drawStartMenu(sf::RenderWindow& window) { };

void game::drawMenu(sf::RenderWindow& window) {
	scaled background(assets::texture::mainMenuBackground, {0, 0}, game::window::factors);

	sf::Vector2f mainMenuPos(100, 200); //menu block position
	std::vector<button> mainMenuButtons = {
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y}, game::window::factors), assets::texture::selectedButton),
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y+100}, game::window::factors), assets::texture::selectedButton),
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y+200}, game::window::factors), assets::texture::selectedButton)
	};

	int focusID = 0; //selected button ID(with arrows)

	int mouseActive = true;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
				window.setMouseCursorVisible(true);

				for(int i=0;i<mainMenuButtons.size();++i){
					if (mainMenuButtons[i].check(sf::Mouse::getPosition(window)) && event.type == sf::Event::MouseButtonPressed) {
						focusID = i;
						std::cout << focusID << std::endl;
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				window.setMouseCursorVisible(false);
				if (event.key.code == game::CONTROL::LEFT_ARROW) {
					focusID = (++focusID) % mainMenuButtons.size();
				}
				if (event.key.code == game::CONTROL::RIGHT_ARROW) {
					focusID = (--focusID + mainMenuButtons.size()) % mainMenuButtons.size();
				}
				if (event.key.code == game::CONTROL::ENTER) {
					std::cout<<focusID<<std::endl;
				}

				for(int i=0;i<mainMenuButtons.size();++i){
					mainMenuButtons[i].update(i == focusID);
				}

			}
		}

		window.clear();
		window.draw(background.getSprite());
		for(int i=0;i<mainMenuButtons.size();++i){
			window.draw(mainMenuButtons[i].getSprite());
		}

		window.display();
	}
};

void game::drawSettings(sf::RenderWindow& window) { };