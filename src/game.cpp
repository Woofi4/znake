#include <iostream>
#include <vector>
#include "../include/game.hpp"
#include "../include/ui/button.hpp"
#include "../include/ui/option.hpp"


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
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Play", assets::font::bebas)),
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y+100}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Settings", assets::font::bebas)),
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y+200}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Exit", assets::font::bebas)),
	};

	int focusID = 0;
	int pressed = -1;

	int firstPress = true;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
				window.setMouseCursorVisible(true);
				firstPress = true;
				for(int i=0;i<mainMenuButtons.size();++i){
					if (mainMenuButtons[i].check(sf::Mouse::getPosition(window)) && event.type == sf::Event::MouseButtonPressed) {
						pressed = i;
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				window.setMouseCursorVisible(false);
				for(int i=0;i<mainMenuButtons.size();++i){
					mainMenuButtons[i].update(i == focusID);
				}
				if(firstPress == true){
					firstPress = false;
					continue;
				}

				if (event.key.code == sf::Keyboard::Down) {
					focusID = (++focusID) % mainMenuButtons.size();
				}
				if (event.key.code == sf::Keyboard::Up) {
					focusID = (--focusID + mainMenuButtons.size()) % mainMenuButtons.size();
				}
				if (event.key.code == sf::Keyboard::Enter) {
					pressed = focusID;
				}

				for(int i=0;i<mainMenuButtons.size();++i){
					mainMenuButtons[i].update(i == focusID);
				}

			}
		}

		switch (pressed) {
			case 0:
				std::cout<<"game";
				pressed = -1;
				break;
			case 1:
				drawSettings(window);
				pressed = -1;
				break;
			case 2:
				window.close();
				break;
		}
		window.clear();
		window.draw(background.getSprite());
		for(int i=0;i<mainMenuButtons.size();++i){
			window.draw(mainMenuButtons[i].getSprite());
			window.draw(mainMenuButtons[i].getText());
		}

		window.display();
	}
};

void game::drawSettings(sf::RenderWindow& window) {
	scaled background(assets::texture::mainMenuBackground, {0, 0}, game::window::factors);

	sf::Vector2f settingsMenuPos(100, 200); //setings block position
	std::vector<option> settingsOptions = {
			option (scaled(assets::texture::button, {settingsMenuPos.x, settingsMenuPos.y}, game::window::factors), assets::texture::selectedButton,
					std::vector<std::string>{"first param", "second param"}),
			option (scaled(assets::texture::button, {settingsMenuPos.x, settingsMenuPos.y+100}, game::window::factors), assets::texture::selectedButton,
					std::vector<std::string>{"1000", "2000"}),
			option (scaled(assets::texture::button, {settingsMenuPos.x, settingsMenuPos.y+200}, game::window::factors), assets::texture::selectedButton,
					std::vector<std::string>{"box", "no wall", "hunger"})
	};

	std::vector<button> settingsButtons = {
			button (scaled(assets::texture::button, {settingsMenuPos.x, settingsMenuPos.y+400}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Back", assets::font::bebas)),
			button (scaled(assets::texture::button, {settingsMenuPos.x+300, settingsMenuPos.y+400}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Save", assets::font::bebas))
	};

	int focusID = 0;
	int pressed = -1;
	bool confirmMode = false;

	while (window.isOpen()&&pressed!=settingsOptions.size()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
				focusID = -1;
				window.setMouseCursorVisible(true);
				confirmMode = false;
				for(int i=0; i < settingsOptions.size(); ++i){
					if (settingsOptions[i].check(sf::Mouse::getPosition(window)) && event.type == sf::Event::MouseButtonPressed) {
						focusID = i;
						settingsOptions[i].next();
					}
				}

				for(int i=0;i<settingsButtons.size();++i){
					if (settingsButtons[i].check(sf::Mouse::getPosition(window)) && event.type == sf::Event::MouseButtonPressed) {
						focusID = i + settingsOptions.size();
						pressed = i + settingsOptions.size();
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				focusID = focusID < 0 ? 0 : focusID;
				window.setMouseCursorVisible(false);
				if (event.key.code == sf::Keyboard::Escape) {
					confirmMode = false;
					focusID = 0;
				}
				if (event.key.code == sf::Keyboard::Enter) {
					if(confirmMode){
						pressed = focusID;
					}else{
						confirmMode = true;
						focusID = settingsOptions.size();
					};
				}
				for(int i=0; i < settingsOptions.size(); ++i){
					settingsOptions[i].update(i == focusID);
				}

				if (event.key.code == sf::Keyboard::Down && !confirmMode) {
					focusID = (++focusID) % settingsOptions.size();
				}
				if (event.key.code == sf::Keyboard::Up && !confirmMode) {
					focusID = (--focusID + settingsOptions.size()) % settingsOptions.size();
				}
				if (event.key.code == sf::Keyboard::Left) {
					if(confirmMode){
						focusID = (--focusID-settingsOptions.size()) % settingsButtons.size()+settingsOptions.size();
					}else{
						settingsOptions[focusID].prev();
					}
				}
				if (event.key.code == sf::Keyboard::Right) {
					if(confirmMode){
						focusID = (++focusID-settingsOptions.size()) % settingsButtons.size()+settingsOptions.size();
					}else{
						settingsOptions[focusID].next();
					}
				}


				for(int i=0; i < settingsOptions.size(); ++i){
					settingsOptions[i].update(i == focusID);
				}
				for(int i=0; i < settingsButtons.size(); ++i){
					settingsButtons[i].update((i + settingsOptions.size()) == focusID);
				}

			}
		}

		switch (pressed-settingsOptions.size()) {
			case 1:
				for(int i=0; i < settingsOptions.size(); ++i){
					std::cout<<settingsOptions[i].getValue()<<std::endl;
				}
				pressed = -1;
				break;
		}

		window.clear();
		window.draw(background.getSprite());
		for(int i=0; i < settingsOptions.size(); ++i){
			window.draw(settingsOptions[i].getSprite());
			window.draw(settingsOptions[i].getText());
		}

		for(int i=0; i < settingsButtons.size(); ++i){
			window.draw(settingsButtons[i].getSprite());
			window.draw(settingsButtons[i].getText());
		}

		window.display();
	}
};