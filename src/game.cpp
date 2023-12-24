#include <iostream>
#include <vector>
#include "../include/game.hpp"
#include "../include/ui/button.hpp"
#include "../include/ui/option.hpp"
#include "../include/ui/textinput.hpp"


namespace game::window {
	std::string title;
	bool fullscreen;
	sf::Vector2f size;
	sf::Vector2f factors;
	const sf::Font& standartFont = assets::font::play;
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

void game::drawStartMenu(sf::RenderWindow& window) {
	scaled background(assets::texture::mainMenuBackground, {0, 0}, game::window::factors);
	std::string current_mode = "Solo";
	int focusID = -1;
	int level = 0;
	sf::Vector2f firstPlayerMenuPos(100, 200);
	std::vector<std::vector<std::any>> levels = {
			std::vector<std::any> {
				textinput (scaled(assets::texture::button, {firstPlayerMenuPos.x, firstPlayerMenuPos.y},
					game::window::factors),	assets::texture::selectedButton),
				option (scaled(assets::texture::button, {firstPlayerMenuPos.x, firstPlayerMenuPos.y+100}, game::window::factors),
					assets::texture::selectedButton,std::vector<std::string>{"color1", "color2"}),
			},
			std::vector<std::any> {
					option (scaled(assets::texture::button, {firstPlayerMenuPos.x+600, firstPlayerMenuPos.y-100}, game::window::factors),
							assets::texture::selectedButton,std::vector<std::string>{"Solo", "Duo"}),
			},
			std::vector<std::any> {
					option (scaled(assets::texture::button, {firstPlayerMenuPos.x, firstPlayerMenuPos.y+300}, game::window::factors),
							assets::texture::selectedButton,std::vector<std::string>{"color1", "color2"}),
					option (scaled(assets::texture::button, {firstPlayerMenuPos.x+300, firstPlayerMenuPos.y+300}, game::window::factors),
							assets::texture::selectedButton,std::vector<std::string>{"color1", "color2"}),
					option (scaled(assets::texture::button, {firstPlayerMenuPos.x+600, firstPlayerMenuPos.y+300}, game::window::factors),
							assets::texture::selectedButton,std::vector<std::string>{"color1", "color2"}),
			}
	};

	std::vector<std::any> SPOption = {
			option (scaled(assets::texture::button, {firstPlayerMenuPos.x+600, firstPlayerMenuPos.y-100}, game::window::factors),
					assets::texture::selectedButton,std::vector<std::string>{"Duo", "Solo"}),
			textinput (scaled(assets::texture::button, {firstPlayerMenuPos.x+600, firstPlayerMenuPos.y},
					game::window::factors),	assets::texture::selectedButton),
			option (scaled(assets::texture::button, {firstPlayerMenuPos.x+600, firstPlayerMenuPos.y+100}, game::window::factors),
					assets::texture::selectedButton,std::vector<std::string>{"color1", "color2"}),
	};
	std::vector<std::any> SPAdd = {
			option (scaled(assets::texture::button, {firstPlayerMenuPos.x+600, firstPlayerMenuPos.y-100}, game::window::factors),
					assets::texture::selectedButton,std::vector<std::string>{"Solo", "Duo"}),
	};

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
				focusID = -1;
				window.setMouseCursorVisible(true);
				for(int floor=0; floor < levels.size(); ++floor){
					for(int i=0; i<levels[floor].size(); ++i){
						auto& type = levels[floor][i].type();
						if(type == typeid(button)){
							if(std::any_cast<button&>(levels[floor][i]).check(sf::Mouse::getPosition(window))){
								focusID = i;
								if(event.type == sf::Event::MouseButtonPressed){
									level = floor;
								}
							}
						}
						if(type == typeid(option)){
							if(std::any_cast<option&>(levels[floor][i]).check(sf::Mouse::getPosition(window))){
								focusID = i;
								if(event.type == sf::Event::MouseButtonPressed){
									level = floor;
									std::any_cast<option&>(levels[floor][i]).next();
								}
							}
						}
						if(type == typeid(textinput)){
							if(std::any_cast<textinput&>(levels[floor][i]).check(sf::Mouse::getPosition(window))){
								focusID = i;
								if(event.type == sf::Event::MouseButtonPressed){
									level = floor;
									window.setMouseCursorVisible(false);
								}
							}
						}
					}
				}
			}else if (event.type == sf::Event::KeyPressed){
				window.setMouseCursorVisible(false);
				if(focusID<0){
					focusID = 0;
					auto& type = levels[level][focusID].type();
					if(type == typeid(button)){	std::any_cast<button&>(levels[level][focusID]).update(1); }
					if(type == typeid(option)){	std::any_cast<option&>(levels[level][focusID]).update(1); }
					if(type == typeid(textinput)){	std::any_cast<textinput&>(levels[level][focusID]).update(1); }
					continue;
				}
				if (event.key.code == sf::Keyboard::Escape) {
					--level;
					if(level<0){
						//action = "Back";
						break;
					}
					focusID = 0;
				}
				if (event.key.code == sf::Keyboard::Enter) {
					level++;
					focusID = 0;
				}
				if (event.TextEntered&&focusID>=0) {
					auto& type = levels[level][focusID].type();
					int d = event.key.shift ? 65 : 97;
					if(0<=event.text.unicode && event.text.unicode<=25){
						if(type == typeid(textinput)){	std::any_cast<textinput&>(levels[level][focusID]).add(event.text.unicode+d); }
					}
					if(26<=event.text.unicode && event.text.unicode<35){
						if(type == typeid(textinput)){	std::any_cast<textinput&>(levels[level][focusID]).add(event.text.unicode+22); }
					}
					if(event.text.unicode == 59){
						if(type == typeid(textinput)){	std::any_cast<textinput&>(levels[level][focusID]).remove(); }
					}
				}
				if (event.key.code == sf::Keyboard::Up) {
					if(level == 2){
						auto& type = levels[level][focusID].type();
						if(type == typeid(option)){	std::any_cast<option&>(levels[level][focusID]).prev(); }
						continue;
					}else{
						focusID = ((--focusID)+levels[level].size()) % levels[level].size();
					}
				}
				if (event.key.code == sf::Keyboard::Down) {
					if(level == 2){
						auto& type = levels[level][focusID].type();
						if(type == typeid(option)){	std::any_cast<option&>(levels[level][focusID]).next(); }
					}else{
						focusID = (++focusID) % levels[level].size();
					}
				}
				if (event.key.code == sf::Keyboard::Left) {
					if(level == 2){
						focusID = ((--focusID)+levels[level].size()) % levels[level].size();
					}else{
						auto& type = levels[level][focusID].type();
						if(type == typeid(option)){	std::any_cast<option&>(levels[level][focusID]).prev(); }
					}
				}
				if (event.key.code == sf::Keyboard::Right) {
					if(level == 2){
						focusID = (++focusID) % levels[level].size();
					}else{
						auto& type = levels[level][focusID].type();
						if(type == typeid(option)){	std::any_cast<option&>(levels[level][focusID]).next(); }
					}
				}
				for(int floor=0; floor < levels.size(); ++floor) {
					for (int i = 0; i < levels[floor].size(); ++i) {
						auto &type = levels[floor][i].type();
						if (type == typeid(button)) { std::any_cast<button &>(levels[floor][i]).update(i == focusID && floor == level); }
						if (type == typeid(option)) { std::any_cast<option &>(levels[floor][i]).update(i == focusID && floor == level); }
						if (type == typeid(textinput)) { std::any_cast<textinput &>(levels[floor][i]).update(i == focusID && floor == level); }
					}
				}
			}
		}



		if(std::any_cast<option&>(levels[1][0]).getValue()!=current_mode){
			current_mode = std::any_cast<option&>(levels[1][0]).getValue();
			if(current_mode == "Solo"){ levels[1] = SPAdd; std::any_cast<option&>(levels[1][0]).update(1); }
			if(current_mode == "Duo"){ levels[1] = SPOption; std::any_cast<option&>(levels[1][0]).update(1); }
		}

		window.clear();
		window.draw(background.getSprite());
		for(int floor=0; floor < levels.size(); ++floor){
			for(int i=0; i < levels[floor].size(); ++i){
				auto& type = levels[floor][i].type();
				if(type == typeid(button)){
					window.draw(std::any_cast<button&>(levels[floor][i]).getSprite());
					window.draw(std::any_cast<button&>(levels[floor][i]).getText());
				}
				if(type == typeid(option)){
					window.draw(std::any_cast<option&>(levels[floor][i]).getSprite());
					window.draw(std::any_cast<option&>(levels[floor][i]).getText());
				}
				if(type == typeid(textinput)){
					window.draw(std::any_cast<textinput&>(levels[floor][i]).getSprite());
					window.draw(std::any_cast<textinput&>(levels[floor][i]).getText());
				}
			}
		}

		window.display();
	}
};

void game::drawMenu(sf::RenderWindow& window) {
	scaled background(assets::texture::mainMenuBackground, {0, 0}, game::window::factors);

	sf::Vector2f mainMenuPos(100, 200); //menu block position
	std::vector<button> mainMenuButtons = {
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Play", game::window::standartFont)),
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y+100}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Settings", window::standartFont)),
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y+200}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Exit", window::standartFont)),
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
				drawStartMenu(window);
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
					assets::texture::selectedButton, sf::Text("Back", window::standartFont)),
			button (scaled(assets::texture::button, {settingsMenuPos.x+300, settingsMenuPos.y+400}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Save", window::standartFont))
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
					if(confirmMode){
						confirmMode = false;
						focusID = 0;
					}else{
						pressed = settingsOptions.size();
						break;
					}

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