#include <iostream>
#include <vector>
#include "../include/game.hpp"
#include "../include/ui/button.hpp"
#include "../include/ui/option.hpp"
#include "../include/ui/textinput.hpp"
#include "../include/obj/drawable_gamemap.hpp"


namespace game::window {
	std::string title;
	bool fullscreen;
	sf::Vector2f size;
	sf::Vector2f factors;
	const int defaultFontSize = 60;
	const sf::Font& textinputFont = assets::font::opensans;
	const sf::Font& standartFont = assets::font::bebas;
}

namespace game::player {
	std::string name;
}

namespace game::properties {
	unsigned speed;
	bool reverseControl;
	bool has2p;
	bool hasBot;
	int roundsCount;
	std::string p2name;
	std::string p1name;
	std::string map;
};


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

	game::properties::speed = 0;
	game::properties::reverseControl = false;
	game::properties::has2p = false;
	game::properties::hasBot = false;
	game::properties::roundsCount = 0;
	game::properties::p2name = "P2";
	game::properties::p1name = "P1";
	game::properties::map = "labyrinth";
	return true;
}

#include <iostream>
void game::drawGame(sf::RenderWindow& window) {
	int round = game::properties::roundsCount;
	int curr = 0;

	int score1p_value = 0;
	int score2p_value = 0;
	sf::Text score1p("0", assets::font::bebas, 60);
	sf::Text score2p("0", assets::font::bebas, 60);

	while (curr != round) {
	sf::Text gameover("Game over", assets::font::bebas, 80);
	sf::Text pause("Paused", assets::font::bebas, 80);


	drawable_gamemap map(game::properties::map == "box" ? assets::map::box : properties::map == "tunnel" ? assets::map::tunnel : assets::map::labyrinth, {window::size.x, window::size.y}, game::properties::has2p, game::properties::hasBot);
	map.setScore1p(score1p_value);
	map.setScore2p(score2p_value);
	drawable_snake& snake = map.getSnake();
	drawable_snake& bot = map.getBot();

	gameover.setPosition((window::size.x / 2) - 180, 200);
	pause.setPosition((window::size.x / 2) - 140, 200);
	score1p.setPosition({map.getMapShape().getPosition().x, map.getMapShape().getPosition().y - 70});
	score2p.setPosition({map.getMapShape().getPosition().x + map.getMapShape().getSize().x - 60, map.getMapShape().getPosition().y - 70});


	unsigned tick = 0;
	std::string direction1p = "EAST";
	std::string direction2p = "EAST";
	bool isAlive = true;
	bool isPause = false;
	bool flag = false;
	while (window.isOpen() && !flag) {
		sf::Event event;

		while (window.pollEvent(event) && !flag) {
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

				if (!isAlive) { curr++; flag = true; }
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
				score1p_value = map.getScore1p();
				score2p_value = map.getScore2p();
				score1p.setString(game::properties::p1name+": "+std::to_string(map.getScore1p()));
				score2p.setString(game::properties::p2name+": "+std::to_string(map.getScore2p()));
			}

			for (const drawable_block& block : map.getWallShapes()) { if (snake.hit(block)) { isAlive = false; }}

			if (game::properties::has2p) {
				for (const drawable_block &block: bot.getSnake()) { if (snake.hit(block)) { isAlive = false; }}
			}
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
	}

	return;
};

void game::drawStartMenu(sf::RenderWindow& window) {
	scaled background(assets::texture::startMenuBackground, {0, 0}, game::window::factors);

	std::string current_mode = "Solo";
	int focusID = -1;
	int level = 0;

	bool exit = false;
	button backButton(scaled(assets::texture::back, {15, 15}, game::window::factors),
					  assets::texture::back_selected, sf::Text("", window::standartFont));

	sf::Vector2f firstPlayerMenuPos(40, 110);
	std::vector<std::vector<std::any>> levels = {
			std::vector<std::any> {
					textinput (scaled(assets::texture::textInput, {firstPlayerMenuPos.x, firstPlayerMenuPos.y+150},
									  game::window::factors),	assets::texture::textInput_selected),
					option (scaled(assets::texture::horizontal_option, {firstPlayerMenuPos.x, firstPlayerMenuPos.y+300}, game::window::factors),
							assets::texture::horizontal_option_selected,std::vector<std::string>{"green", "red", "blue"}),
			},
			std::vector<std::any> {
					option (scaled(assets::texture::horizontal_option, {firstPlayerMenuPos.x+800, firstPlayerMenuPos.y}, game::window::factors),
							assets::texture::horizontal_option_selected,std::vector<std::string>{"Solo", "Duo"}),
			},
			std::vector<std::any> {
					option (scaled(assets::texture::vertical_option, {firstPlayerMenuPos.x, firstPlayerMenuPos.y+520}, game::window::factors),
							assets::texture::vertical_option_selected,std::vector<std::string>{"0", "1"}),
					option (scaled(assets::texture::vertical_option, {firstPlayerMenuPos.x+400, firstPlayerMenuPos.y+520}, game::window::factors),
							assets::texture::vertical_option_selected,std::vector<std::string>{"box", "tunnel", "labyrinth"}),
					option (scaled(assets::texture::vertical_option, {firstPlayerMenuPos.x+800, firstPlayerMenuPos.y+520}, game::window::factors),
							assets::texture::vertical_option_selected,std::vector<std::string>{"1", "2", "3", "4", "5", "6"}),
			},
			std::vector<std::any> {
					button (scaled(assets::texture::startbutton, {440, 15}, game::window::factors),
							assets::texture::startselectedButton, sf::Text("START", window::standartFont))
			}
	};

	std::vector<std::any> SPOption = {
			option (scaled(assets::texture::horizontal_option, {firstPlayerMenuPos.x+800, firstPlayerMenuPos.y}, game::window::factors),
					assets::texture::horizontal_option_selected,std::vector<std::string>{"Duo", "Solo"}),
			textinput (scaled(assets::texture::textInput, {firstPlayerMenuPos.x+800, firstPlayerMenuPos.y+150},
							  game::window::factors),	assets::texture::textInput_selected),
			option (scaled(assets::texture::horizontal_option, {firstPlayerMenuPos.x+800, firstPlayerMenuPos.y+300}, game::window::factors),
					assets::texture::horizontal_option_selected,std::vector<std::string>{"green", "red", "blue"}),
	};
	std::vector<std::any> SPAdd = {
			option (scaled(assets::texture::horizontal_option, {firstPlayerMenuPos.x+800, firstPlayerMenuPos.y}, game::window::factors),
					assets::texture::horizontal_option_selected,std::vector<std::string>{"Solo", "Duo"}),
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
									if(std::any_cast<button&>(levels[floor][i]).getText().getString()=="START") {
										exit = true;

										game::properties::has2p = (std::any_cast<option&>(levels[1][0]).getValue()=="Duo")?true:false;
										game::properties::hasBot = (std::any_cast<option&>(levels[2][0]).getValue()=="1")?true:false;
										game::properties::roundsCount = stoi(std::any_cast<option&>(levels[2][2]).getValue());
										game::properties::map = std::any_cast<option&>(levels[2][1]).getValue();
										game::properties::p1name = std::any_cast<textinput&>(levels[0][0]).getValue();
										if(game::properties::has2p){
											game::properties::p2name = std::any_cast<textinput&>(levels[1][1]).getValue();
										}

										drawGame(window);
									}
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
					if(level>=levels.size()){
						game::properties::has2p = (std::any_cast<option&>(levels[1][0]).getValue()=="Duo")?true:false;
						game::properties::hasBot = (std::any_cast<option&>(levels[2][0]).getValue()=="1")?true:false;
						game::properties::roundsCount = stoi(std::any_cast<option&>(levels[2][2]).getValue());
						game::properties::map = std::any_cast<option&>(levels[2][1]).getValue();
						game::properties::p1name = std::any_cast<textinput&>(levels[0][0]).getValue();
						if(game::properties::has2p){
							game::properties::p2name = std::any_cast<textinput&>(levels[1][1]).getValue();
						}

						drawGame(window);
						exit = true;
						break;
					}
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
						focusID = (++focusID) % levels[level].size();
					}
				}
				if (event.key.code == sf::Keyboard::Down) {
					if(level == 2){
						auto& type = levels[level][focusID].type();
						if(type == typeid(option)){	std::any_cast<option&>(levels[level][focusID]).next(); }
					}else{
						focusID = ((--focusID)+levels[level].size()) % levels[level].size();
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

		if(std::any_cast<option&>(levels[2][1]).getValue()=="box"){
			scaled box(assets::texture::box_prev, {390, 200}, game::window::factors);
			window.draw(box.getSprite());
		}
		if(std::any_cast<option&>(levels[2][1]).getValue()=="tunnel"){
			scaled box(assets::texture::tunnel_prev, {390, 200}, game::window::factors);
			window.draw(box.getSprite());
		}
		if(std::any_cast<option&>(levels[2][1]).getValue()=="labyrinth"){
			scaled box(assets::texture::labyrinth_prev, {390, 200}, game::window::factors);
			window.draw(box.getSprite());
		}

		window.display();
	}
};

void game::drawMenu(sf::RenderWindow& window) {
	scaled background(assets::texture::mainMenuBackground, {0, 0}, game::window::factors);

	std::vector<sf::Text> mainMenuText = {
			sf::Text("Znake", assets::font::bebas)
	};

	mainMenuText[0].setPosition(350*window::factors.x, 50*window::factors.y);
	mainMenuText[0].setCharacterSize(window::defaultFontSize*2*window::factors.x);
	mainMenuText[0].setFillColor(sf::Color(255,0,0));

	sf::Vector2f mainMenuPos(100, 200); //menu block position
	std::vector<button> mainMenuButtons = {
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Play", game::window::standartFont)),
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y+200}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Settings", window::standartFont)),
			button (scaled(assets::texture::button, {mainMenuPos.x, mainMenuPos.y+400}, game::window::factors),
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
		window.draw(mainMenuText[0]);
		window.draw(background.getSprite());
		for(int i=0;i<mainMenuButtons.size();++i){
			window.draw(mainMenuButtons[i].getSprite());
			window.draw(mainMenuButtons[i].getText());
		}

		window.display();
	}
};

void game::drawSettings(sf::RenderWindow& window) {
	scaled background(assets::texture::settingsBackground, {0, 0}, game::window::factors);

	sf::Vector2f settingsMenuPos(650, 100); //setings block position

	std::vector<std::string> resolutions = {"1200x800", "1600x1200", "1920x1080"};
	std::vector<option> settingsOptions = {
			option (scaled(assets::texture::horizontal_option, {settingsMenuPos.x, settingsMenuPos.y}, game::window::factors), assets::texture::horizontal_option_selected,
					resolutions),
			option (scaled(assets::texture::horizontal_option, {settingsMenuPos.x, settingsMenuPos.y+200}, game::window::factors), assets::texture::horizontal_option_selected,
					std::vector<std::string>{"fullscreen", "window"}),
			option (scaled(assets::texture::horizontal_option, {settingsMenuPos.x, settingsMenuPos.y+400}, game::window::factors), assets::texture::horizontal_option_selected,
					std::vector<std::string>{"Arrows", "WASD"})
	};

	std::vector<button> settingsButtons = {
			button (scaled(assets::texture::button, {settingsMenuPos.x-500, settingsMenuPos.y+550}, game::window::factors),
					assets::texture::selectedButton, sf::Text("Back", window::standartFont)),
			button (scaled(assets::texture::button, {settingsMenuPos.x, settingsMenuPos.y+550}, game::window::factors),
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
				game::properties::reverseControl = settingsOptions[2].getValue()=="Arrows"?true:false;
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