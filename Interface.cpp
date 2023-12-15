#include "Interface.hpp"
#include <string>
#include "TextBox.h"
using namespace sf;

const int SCRWIDTH = 800;
const int SCRHEIGHT = 900;

void draw_start(RenderWindow& window, Texture backgroundTexture) {
	Texture t0, set;

	t0.loadFromFile("fontPic/khung.png");

	set.loadFromFile("fontPic/settingButton.png");
	Sprite start(t0);
	Sprite settingBut(set);

	start.setPosition(200, 400);
	start.setScale(static_cast<float>(210) / backgroundTexture.getSize().x, static_cast<float>(130) / backgroundTexture.getSize().y);
	settingBut.setPosition(700, 30);
	settingBut.setScale(static_cast<float>(150) / backgroundTexture.getSize().x, static_cast<float>(80) / backgroundTexture.getSize().y);



	Font f; f.loadFromFile("fontPic/game.ttf");
	Text gameName;
	gameName.setFont(f);
	gameName.setCharacterSize(100);
	gameName.setFillColor(Color(255, 202, 21));
	gameName.setOutlineColor(Color(236, 147, 65));
	gameName.setOutlineThickness(4);
	gameName.setString("TETRIS");
	gameName.setPosition(250, 130);

	Text startText;
	startText.setFont(f);
	startText.setCharacterSize(80);
	startText.setFillColor(Color(130, 17, 172));
	startText.setOutlineColor(Color::Black);
	startText.setOutlineThickness(0);
	startText.setString("START");
	startText.setPosition(295, 455);

	window.draw(gameName);
	window.draw(start);
	window.draw(startText);
	window.draw(settingBut);
}

void draw_home_without_login(RenderWindow& window, Texture backgroundTexture) {
	draw_start(window, backgroundTexture);
	Texture t1, t2;

	t1.loadFromFile("fontPic/khung.png");
	t2.loadFromFile("fontPic/khung.png");
	;
	Sprite login(t1);
	Sprite registerr(t2);
	login.setPosition(250, 555);
	login.setScale(static_cast<float>(160) / backgroundTexture.getSize().x, static_cast<float>(100) / backgroundTexture.getSize().y);
	registerr.setPosition(250, 679);
	registerr.setScale(static_cast<float>(160) / backgroundTexture.getSize().x, static_cast<float>(100) / backgroundTexture.getSize().y);


	Font f; f.loadFromFile("fontPic/game.ttf");
	Text gameName;
	gameName.setFont(f);
	gameName.setCharacterSize(100);
	gameName.setFillColor(Color(255, 202, 21));
	gameName.setOutlineColor(Color(236, 147, 65));
	gameName.setOutlineThickness(4);
	gameName.setString("TETRIS");
	gameName.setPosition(250, 130);

	Text loginText;
	loginText.setFont(f);
	loginText.setCharacterSize(50);
	loginText.setFillColor(Color(130, 17, 172));
	loginText.setOutlineColor(Color::Black);
	loginText.setOutlineThickness(0);
	loginText.setString("Login");
	loginText.setPosition(345, 602);

	Text regisText;
	regisText.setFont(f);
	regisText.setCharacterSize(50);
	regisText.setFillColor(Color(130, 17, 172));
	regisText.setOutlineColor(Color::Black);
	regisText.setOutlineThickness(0);
	regisText.setString("Register");
	regisText.setPosition(315, 730);

	Text welcome;
	Font bubble; bubble.loadFromFile("fontPic/bubble.otf");
	welcome.setFont(bubble);
	welcome.setCharacterSize(180);
	welcome.setFillColor(Color(33, 138, 200));
	welcome.setOutlineColor(Color::Black);
	welcome.setOutlineThickness(0);
	welcome.setString("WELCOME");
	sf::FloatRect textBounds = welcome.getLocalBounds();
	welcome.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	welcome.setPosition(window.getSize().x / 2.0f, 350);

	window.draw(welcome);
	window.draw(gameName);
	window.draw(login);
	window.draw(registerr);
	window.draw(loginText);
	window.draw(regisText);
}

void draw_home_with_login(sf::RenderWindow& window, sf::Texture backgroundTexture, std::string playerName) {
	draw_start(window, backgroundTexture);
	Text welcome;
	Font bubble; bubble.loadFromFile("fontPic/bubble.otf");
	welcome.setFont(bubble);
	welcome.setCharacterSize(180);
	welcome.setFillColor(Color(33, 138, 200));
	welcome.setString("Hi " + playerName);
	sf::FloatRect textBounds = welcome.getLocalBounds();
	welcome.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	welcome.setPosition(window.getSize().x / 2.0f, 350);
	sf::Texture high;
	if (!high.loadFromFile("fontPic/highestScore.png")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite highBoard(high);
	highBoard.setScale(static_cast<float>(500) / high.getSize().x, static_cast<float>(320) / high.getSize().y);
	highBoard.setPosition(160, 570);
	window.draw(highBoard);
	window.draw(welcome);
}

void draw_login_interface(sf::RenderWindow& window, sf::Sprite Back, sf::Sprite Submit, sf::Sprite Email, sf::Sprite Password) {
	sf::Texture loginBackgroundTexture;
	if (!loginBackgroundTexture.loadFromFile("fontPic/loginBack.jpg")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite loginBack(loginBackgroundTexture);
	loginBack.setScale(static_cast<float>(810) / loginBackgroundTexture.getSize().x, static_cast<float>(900) / loginBackgroundTexture.getSize().y);
	loginBack.setPosition(-5, -5);
	sf::Texture login2;
	if (!login2.loadFromFile("fontPic/loginBack2.jpg")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite log(login2);
	log.setScale(static_cast<float>(850) / login2.getSize().x, static_cast<float>(950) / login2.getSize().y);
	log.setPosition(-5, -5);

	window.draw(loginBack);
	window.draw(log);

	Submit.setPosition(230, 405);
	Submit.setScale(static_cast<float>(350) / loginBackgroundTexture.getSize().x, static_cast<float>(300) / loginBackgroundTexture.getSize().y);
	window.draw(Submit);

	Password.setPosition(20, 225);
	Password.setScale(static_cast<float>(250) / loginBackgroundTexture.getSize().x, static_cast<float>(200) / loginBackgroundTexture.getSize().y);
	window.draw(Password);

	Email.setPosition(20, 50);
	Email.setScale(static_cast<float>(250) / loginBackgroundTexture.getSize().x, static_cast<float>(200) / loginBackgroundTexture.getSize().y);
	window.draw(Email);

	Back.setPosition(275, 530);
	Back.setScale(static_cast<float>(330) / loginBackgroundTexture.getSize().x, static_cast<float>(270) / loginBackgroundTexture.getSize().y);
	window.draw(Back);
	//window.draw(te);
}

void draw_register_interface(sf::RenderWindow& window, sf::Sprite Back, sf::Sprite Submit, sf::Sprite Email, sf::Sprite Password) {
	Texture t3, t4, t5, t6, t8, t9;
	t8.loadFromFile("fontPic/Password.png");
	Sprite ConfirmPassword(t8);
	sf::Texture loginBackgroundTexture;
	if (!loginBackgroundTexture.loadFromFile("fontPic/loginBack.jpg")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite regBack(loginBackgroundTexture);
	regBack.setScale(static_cast<float>(810) / loginBackgroundTexture.getSize().x, static_cast<float>(900) / loginBackgroundTexture.getSize().y);
	regBack.setPosition(-5, -5);
	window.draw(regBack);
	sf::Texture login2;
	if (!login2.loadFromFile("fontPic/loginBack2.jpg")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite log(login2);
	log.setScale(static_cast<float>(850) / login2.getSize().x, static_cast<float>(950) / login2.getSize().y);
	log.setPosition(-5, -5);
	window.draw(log);

	Submit.setPosition(230, 505);
	Submit.setScale(static_cast<float>(350) / loginBackgroundTexture.getSize().x, static_cast<float>(300) / loginBackgroundTexture.getSize().y);
	window.draw(Submit);

	Back.setPosition(275, 630);
	Back.setScale(static_cast<float>(330) / loginBackgroundTexture.getSize().x, static_cast<float>(270) / loginBackgroundTexture.getSize().y);
	window.draw(Back);

	Email.setPosition(15, 34);
	Email.setScale(static_cast<float>(250) / loginBackgroundTexture.getSize().x, static_cast<float>(200) / loginBackgroundTexture.getSize().y);
	window.draw(Email);

	Password.setPosition(15, 198);
	Password.setScale(static_cast<float>(250) / loginBackgroundTexture.getSize().x, static_cast<float>(200) / loginBackgroundTexture.getSize().y);
	window.draw(Password);

	ConfirmPassword.setPosition(15, 340);
	ConfirmPassword.setScale(static_cast<float>(250) / loginBackgroundTexture.getSize().x, static_cast<float>(200) / loginBackgroundTexture.getSize().y);
	window.draw(ConfirmPassword);
}

void draw_setting(sf::RenderWindow& window, bool sound_mode, bool music_mode) {
	window.clear();

	sf::Texture blur;
	if (!blur.loadFromFile("fontPic/blurBack.png")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite blurHome(blur);
	blurHome.setScale(static_cast<float>(900) / blur.getSize().x, static_cast<float>(900) / blur.getSize().y);
	blurHome.setPosition(0, 0);

	sf::Texture settingFrame;
	if (!settingFrame.loadFromFile("fontPic/setting.png")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite setting(settingFrame);
	setting.setScale(static_cast<float>(450) / settingFrame.getSize().x, static_cast<float>(500) / settingFrame.getSize().y);
	setting.setPosition(170, 174);

	sf::Texture sound;
	if (sound_mode == 0) {
		if (!sound.loadFromFile("fontPic/mute.png")) {
			std::cerr << "Error loading background texture" << std::endl;
			return;
		}
	}
	else {
		if (!sound.loadFromFile("fontPic/volumeOn.png")) {
			std::cerr << "Error loading background texture" << std::endl;
			return;
		}
	}

	sf::Sprite soundBut(sound);
	soundBut.setScale(static_cast<float>(100) / sound.getSize().x, static_cast<float>(90) / sound.getSize().y);
	soundBut.setPosition(260, 342);

	sf::Texture music;
	if (music_mode == 0) {
		if (!music.loadFromFile("fontPic/musicOff.png")) {
			std::cerr << "Error loading background texture" << std::endl;
			return;
		}
	}
	else {
		if (!music.loadFromFile("fontPic/musicOn.png")) {
			std::cerr << "Error loading background texture" << std::endl;
			return;
		}
	}
	sf::Sprite musicBut(music);
	musicBut.setScale(static_cast<float>(100) / music.getSize().x, static_cast<float>(85) / music.getSize().y);
	musicBut.setPosition(420, 342);

	Font f; f.loadFromFile("fontPic/game.ttf");
	Text easy;
	easy.setFont(f);
	easy.setCharacterSize(40);
	easy.setFillColor(Color::Black);
	easy.setString("Easy");
	sf::FloatRect textBounds = easy.getLocalBounds();
	easy.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	easy.setPosition(window.getSize().x / 2.0f - 5, 478);

	Text med;
	med.setFont(f);
	med.setCharacterSize(40);
	med.setFillColor(Color::Black);
	med.setString("Medium");
	textBounds = med.getLocalBounds();
	med.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	med.setPosition(window.getSize().x / 2.0f - 5, 540);

	Text hard;
	hard.setFont(f);
	hard.setCharacterSize(40);
	hard.setFillColor(Color::Black);
	hard.setString("Hard");
	textBounds = hard.getLocalBounds();
	hard.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);
	hard.setPosition(window.getSize().x / 2.0f - 5, 600);

	window.draw(blurHome);
	window.draw(setting);
	window.draw(easy);
	window.draw(med);
	window.draw(hard);
	window.draw(soundBut);
	window.draw(musicBut);

}

void draw_gameOver(sf::RenderWindow& window, int scoreCur) {
	Font f; f.loadFromFile("fontPic/game.ttf");
	Text overText;
	overText.setFont(f);
	overText.setCharacterSize(100);
	overText.setFillColor(Color(255, 202, 21));
	overText.setOutlineColor(Color(236, 147, 65));
	overText.setOutlineThickness(4);
	overText.setString("GAME OVER");
	overText.setPosition(145, 110);

	Text score;
	score.setFont(f);
	score.setCharacterSize(60);
	score.setFillColor(Color(236, 147, 65));
	score.setString("SCORE");
	score.setPosition(180, 255);

	Font num; 
	if (!f.loadFromFile("resoure/CallOfOpsDutyIi-7Bgm4.ttf"))
	{
		std::cerr << "Error loading font: " << "resoure/CallOfOpsDutyIi-7Bgm4.ttf" << std::endl;
	}
	Text scoreNum;
	scoreNum.setFont(f);
	scoreNum.setCharacterSize(60);
	scoreNum.setFillColor(Color(236, 147, 65));
	scoreNum.setString(std::to_string(scoreCur));
	scoreNum.setPosition(350, 255);

	Text highest;
	highest.setFont(f);
	highest.setCharacterSize(50);
	highest.setFillColor(Color::Yellow);
	highest.setOutlineColor(Color(236, 147, 65));
	highest.setOutlineThickness(4);
	highest.setString("Highest \n score");
	highest.setPosition(180, 330);

	Text home;
	home.setFont(f);
	home.setCharacterSize(30);
	home.setFillColor(Color::Black);
	home.setString("Home");
	home.setPosition(510, 480);

	Text replay;
	replay.setFont(f);
	replay.setCharacterSize(30);
	replay.setFillColor(Color::Black);
	replay.setString("Restart");
	replay.setPosition(500, 390);

	sf::Texture gameOver;
	if (!gameOver.loadFromFile("fontPic/gameOver.png")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite gameOverIn(gameOver);
	gameOverIn.setScale(static_cast<float>(1700) / gameOver.getSize().x, static_cast<float>(1200) / gameOver.getSize().y);
	gameOverIn.setPosition(-430, -150);

	window.draw(gameOverIn);
	window.draw(overText);
	window.draw(score);
	window.draw(highest);
	window.draw(home);
	window.draw(scoreNum);
	window.draw(replay);
}