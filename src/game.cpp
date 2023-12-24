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
	const int defaultFontSize = 30;
	const sf::Font& textinputFont = assets::font::opensans;
	const sf::Font& standartFont = assets::font::bebas;
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

	player::name = config["player"]["name"];

	return true;
}

#include <iostream>
void game::drawGame(sf::RenderWindow& window) {
	sf::Text gameover("Game over", assets::font::arcade, 80);
	sf::Text pause("Paused", assets::font::arcade, 80);
	sf::Text score1p("0", assets::font::arcade, 60);
	sf::Text score2p("0", assets::font::arcade, 60);

	drawable_gamemap map(assets::map::box, window::size, game::properties::has2p, game::properties::hasBot);
	drawable_snake& snake = map.getSnake();
	drawable_snake& bot = map.getBot();

	gameover.setPosition((window::size.first / 2) - 180, 200);
	pause.setPosition((window::size.first / 2) - 140, 200);
	score1p.setPosition({map.getMapShape().getPosition().x, map.getMapShape().getPosition().y - 70});
	score2p.setPosition({map.getMapShape().getPosition().x + map.getMapShape().getSize().x - 60, map.getMapShape().getPosition().y - 70});


	unsigned tick = 0;
	std::string direction1p = "EAST";
	std::string direction2p = "EAST";
	bool isAlive = true;
	bool isPause = false;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					direction1p = "NORTH";
				}
				else if (event.key.code == sf::Keyboard::A) {
					direction1p = "WEST";
				}
				else if (event.key.code == sf::Keyboard::S) {
					direction1p = "SOUTH";
				}
				else if (event.key.code == sf::Keyboard::D) {
					direction1p = "EAST";
				}

				if (event.key.code == sf::Keyboard::Up) {
					direction2p = "NORTH";
				}
				else if (event.key.code == sf::Keyboard::Left) {
					direction2p = "WEST";
				}
				else if (event.key.code == sf::Keyboard::Down) {
					direction2p = "SOUTH";
				}
				else if (event.key.code == sf::Keyboard::Right) {
					direction2p = "EAST";
				}

				else if (event.key.code == sf::Keyboard::Escape) {
					isPause = !isPause;
				}

				// Убрать
				if (!isAlive) { return; }
			}
		}

		if (isAlive && !isPause) {
			window.clear();
			window.draw(map.getMapShape());
			window.draw(score1p);
			if (game::properties::has2p) {
				window.draw(score2p);
			}
			window.draw(map.getCommonShape());
			if (map.hasBooster()) {
				window.draw(map.getBoosterShape());
			}

			for (const drawable_block& block : map.getWallShapes()) { window.draw(block.getShape()); }
			for (const drawable_block& block : snake.getSnake()) { window.draw(block.getShape()); }
			if (game::properties::has2p) {
				for (const drawable_block& block : bot.getSnake()) { window.draw(block.getShape()); }
			}

			if ((tick % (snake::maxSpeed - properties::speed) == 0)) {
				snake.move(game::properties::reverseControl ? direction2p : direction1p);
				if (game::properties::has2p && !game::properties::hasBot) { bot.move(game::properties::reverseControl ? direction1p : direction2p); };
				map.update();
				score1p.setString(std::to_string(map.getScore1p()));
				score2p.setString(std::to_string(map.getScore2p()));
			}

			for (const drawable_block& block : map.getWallShapes()) { if (snake.hit(block)) { isAlive = false; }}
			for (const drawable_block& block : bot.getSnake()) { if (snake.hit(block)) { isAlive = false; }}
			std::vector<drawable_block> snake_blocks = snake.getSnake();
			for (unsigned i = 1; i < snake_blocks.size(); ++i) { if (snake.hit(snake_blocks[i])) { isAlive = false; } }

			if (game::properties::has2p) {
				for (const drawable_block& block : map.getWallShapes()) { if (bot.hit(block)) { isAlive = false; }}
				for (const drawable_block& block : snake.getSnake()) { if (bot.hit(block)) { isAlive = false; }}
				std::vector<drawable_block> bot_blocks = bot.getSnake();
				for (unsigned i = 1; i < bot_blocks.size(); ++i) { if (bot.hit(bot_blocks[i])) { isAlive = false; } }
			}

			if (++tick == window::framerate) { tick = 0; }
		}
		else if (isPause) {
			window.draw(pause);
		}
		else if (!isAlive) {
			window.draw(gameover);
		}

		window.display();
	}
};

void game::drawStartMenu(sf::RenderWindow& window) {
	scaled background(assets::texture::mainMenuBackground, {0, 0}, game::window::factors);

	std::string current_mode = "Solo";
	int focusID = -1;
	int level = 0;

	bool exit = false;
	button backButton(scaled(assets::texture::button, {100, 100}, game::window::factors),
			assets::texture::selectedButton, sf::Text("Back", window::standartFont));

	sf::Vector2f firstPlayerMenuPos(200, 200);
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

	while (window.isOpen()&&!exit) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }
			else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
				focusID = -1;
				window.setMouseCursorVisible(true);
				if (backButton.check(sf::Mouse::getPosition(window)) && event.type == sf::Event::MouseButtonPressed) {
					exit = true;
				}
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
				backButton.update(0);
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
						exit = true;
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

		window.draw(backButton.getSprite());
		window.draw(backButton.getText());

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