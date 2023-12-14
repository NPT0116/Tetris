#include "Headers/Interface.h"
#include "TextBox.h"
using namespace sf;

const int SCRWIDTH = 800;
const int SCRHEIGHT = 900;

void draw_home_without_login(RenderWindow& window, Texture backgroundTexture) {
	Texture t1, t2, t0;

	t0.loadFromFile("fontPic/startRec.png");
	t1.loadFromFile("fontPic/loginRec.png");
	t2.loadFromFile("fontPic/regisRec.png");

	Sprite start(t0);
	Sprite login(t1);
	Sprite registerr(t2);

	login.setPosition(233, 607);
	login.setScale(static_cast<float>(810) / backgroundTexture.getSize().x, static_cast<float>(600) / backgroundTexture.getSize().y);
	registerr.setPosition(233, 720);
	registerr.setScale(static_cast<float>(810) / backgroundTexture.getSize().x, static_cast<float>(750) / backgroundTexture.getSize().y);
	start.setPosition(170, 470);
	start.setScale(static_cast<float>(810) / backgroundTexture.getSize().x, static_cast<float>(900) / backgroundTexture.getSize().y);

	Font f; f.loadFromFile("fontPic/game.ttf");
	Text gameName;
	gameName.setFont(f);
	gameName.setCharacterSize(80);
	gameName.setFillColor(Color(226, 226, 227));
	gameName.setString("TETRIS");
	gameName.setPosition(280, 130);

	Text grName;
	grName.setFont(f);
	grName.setCharacterSize(50);
	grName.setFillColor(Color(226, 226, 227));
	grName.setString("Gr Tennn");
	grName.setPosition(310, 215);

	Text startText;
	startText.setFont(f);
	startText.setCharacterSize(80);
	startText.setFillColor(Color(249, 214, 7));
	startText.setOutlineColor(Color::Black);
	startText.setOutlineThickness(3);
	startText.setString("START");
	startText.setPosition(295, 455);

	Text loginText;
	loginText.setFont(f);
	loginText.setCharacterSize(50);
	loginText.setFillColor(Color(249, 214, 7));
	loginText.setOutlineColor(Color::Black);
	loginText.setOutlineThickness(3);
	loginText.setString("Login");
	loginText.setPosition(345, 602);

	Text regisText;
	regisText.setFont(f);
	regisText.setCharacterSize(50);
	regisText.setFillColor(Color(249, 214, 7));
	regisText.setOutlineColor(Color::Black);
	regisText.setOutlineThickness(3);
	regisText.setString("Register");
	regisText.setPosition(315, 695);

	window.draw(gameName);
	window.draw(grName);
	window.draw(start);
	window.draw(login);
	window.draw(registerr);
	window.draw(startText);
	window.draw(loginText);
	window.draw(regisText);
}

void draw_home_with_login(sf::RenderWindow& window, sf::Texture backgroundTexture, std::string playerName) {
	draw_home_without_login(window, backgroundTexture);
	Font f; f.loadFromFile("fontPic/game.ttf");
	Text welcome;
	welcome.setFont(f);
	welcome.setCharacterSize(150);
	welcome.setFillColor(Color(249, 171, 15));
	welcome.setOutlineColor(Color::Black);
	welcome.setOutlineThickness(3);
	welcome.setString("Hi " + playerName);
	sf::FloatRect textRect = welcome.getLocalBounds();
	welcome.setOrigin(textRect.width / 2, textRect.height / 2);
	welcome.setPosition(sf::Vector2f(SCRWIDTH / 2.0f, 320));
	sf::Texture high;
	if (!high.loadFromFile("fontPic/highestScore.png")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite highBoard(high);
	highBoard.setScale(static_cast<float>(500) / high.getSize().x, static_cast<float>(320) / high.getSize().y);
	highBoard.setPosition(160, 570);

	sf::Texture backBoard;
	if (!backBoard.loadFromFile("fontPic/loginBack.jpg")) {
		std::cerr << "Error loading background texture" << std::endl;
		return;
	}
	sf::Sprite bb(backBoard);
	bb.setScale(static_cast<float>(480) / backBoard.getSize().x, static_cast<float>(500) / backBoard.getSize().y);
	bb.setPosition(170, 580);
	window.draw(bb);
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

	window.draw(loginBack);
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