#include "Tetris.h"
using namespace sf;
//login
struct scn2
{
    bool email = false;
    bool password = false;
};

struct scn3
{
    bool email = false;
    bool confirmEmail = false;
    bool password = false;
    bool confirmPassword = false;
};

struct account
{
    std::string email;
    std::string password;
};

int scene = 1, i = 1;
scn2 scene2;
scn3 scene3;
account acc[100];
bool first = true;

void input()
{
    std::ifstream fin("data.txt", std::ios::in | std::ios::out);
    while (fin >> acc[i].email)
    {
        fin >> acc[i].password;
        i++;
    }
    fin.close();
}

//-------------------------

bool trigger_event(Clock& clock, float& elapsedTime, float interval)
{
    Time pass = clock.getElapsedTime();
    elapsedTime += pass.asSeconds();
    clock.restart();
    if (elapsedTime >= interval)
    {
        elapsedTime = 0.0f;
        return true;
    }
    return false;
}

sf::Text createText(const std::string& fontPath, const std::string& textString, int characterSize, const sf::Color& fillColor, float posX, float posY)
{
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile(fontPath))
    {
        std::cerr << "Error loading font: " << fontPath << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(fillColor);
    text.setString(textString);
    text.setPosition(posX, posY);

    return text;
}

sf::RectangleShape createRectangleShape(float sizeX, float sizeY, float posX, float posY, const sf::Color& fillColor)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(sizeX, sizeY));
    rectangle.setPosition(posX, posY);
    rectangle.setFillColor(fillColor);

    return rectangle;
}

void playGame(ofstream &fout, int cell, int column, int row, int screen_size) {

	RenderWindow gameWindow(VideoMode(/*cell * column * screen_size * 2.6*/800, /*cell * row * screen_size * 1.4*/900), "Tetris", Style::Close);
	gameWindow.setView(View(FloatRect(-3, -2, 212, 165)));
    //text - ingame
    string font = "resoure/CallOfOpsDutyIi-7Bgm4.ttf";
    sf::Font f; int characterSize = 15; sf::Color fillColor = sf::Color::White;
    if (!f.loadFromFile(font))
    {
        std::cerr << "Error loading font: " << font << std::endl;
    }
    Text nextBlock;
    nextBlock.setFont(f);
    nextBlock.setCharacterSize(characterSize);
    nextBlock.setFillColor(fillColor);
    nextBlock.setString("Next");
    nextBlock.setPosition(95, 97);
    Text score;
    score.setFont(f);
    score.setCharacterSize(characterSize);
    score.setFillColor(fillColor);
    score.setString("Score");
    score.setPosition(92, 7);
    Text speed;
    speed.setFont(f);
    speed.setCharacterSize(characterSize);
    speed.setFillColor(fillColor);
    speed.setString("Speed");
    speed.setPosition(92, 51);

    //Game - inteerface
    Tetris tetris;

    RectangleShape cellShape(Vector2f(cell - 1, cell - 1));
    cellShape.setFillColor(Color(36, 36, 88));

    //background - ingame
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("resoure/new.jpg")) {
        std::cerr << "Error loading background texture" << std::endl;
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(400) / backgroundTexture.getSize().x, static_cast<float>(170) / backgroundTexture.getSize().y);
    backgroundSprite.setPosition(-5, -5);

    //dropping
   // sf::Clock clock;
    float elapsedTime = 0.0f;
    float interval = 0.5f; // 1 second interval
    gameWindow.clear(Color(0, 0, 0));

    //shapes
    sf::RectangleShape recScore = createRectangleShape(40, 20, 88, 26, sf::Color(39, 139, 75));
    sf::RectangleShape recScoreShadow = createRectangleShape(40, 20, 90, 28, sf::Color(11, 66, 35));
    sf::RectangleShape recSpeed = createRectangleShape(40, 20, 88, 70, sf::Color(173, 7, 31));
    sf::RectangleShape recSpeedShadow = createRectangleShape(40, 20, 90, 72, sf::Color(60, 0, 0));
    sf::RectangleShape recNext = createRectangleShape(40, 40, 88, 116, sf::Color(6, 171, 165));
    sf::RectangleShape recNextShadow = createRectangleShape(40, 40, 90, 118, sf::Color(0, 72, 78));
    sf::RectangleShape recBack = createRectangleShape(81.5, 161.5, -1, -1, sf::Color(30, 6, 64));
	gameWindow.setView(View(FloatRect(-3, -2, 140, 165)));
	while (gameWindow.isOpen())
	{
		gameWindow.setFramerateLimit(20000);
		Event event;
		tetris.Drop_ghost_block();
		while (gameWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
				gameWindow.close();
			if (event.type == Event::KeyPressed)
			{
				tetris.hand_input(event, gameWindow);
			}
		}
		if (tetris.drop_block == true)
		{

			tetris.moveBlockDown(gameWindow);
		}
		if (trigger_event(tetris.clock_event, tetris.elapsedTime, tetris.interval))
		{
			tetris.moveBlockDown(gameWindow);
		}
		{
			gameWindow.clear(Color(0, 0, 0));
			//cout << "clear" << endl;
		}
		gameWindow.draw(backgroundSprite);
		gameWindow.draw(recBack);


		tetris.Draw(gameWindow);
		//rec
		gameWindow.draw(recNextShadow);
		gameWindow.draw(recScoreShadow);
		gameWindow.draw(recSpeedShadow);
		gameWindow.draw(recNext);
		gameWindow.draw(recScore);
		gameWindow.draw(recSpeed);
		//text
		// Thời gian và tăng tốc độ
		if (!tetris.gameOver) {
			tetris.end = clock();
		}
		float runned_time = (float)(tetris.end - tetris.begin) / CLOCKS_PER_SEC;
		stringstream stream;
		stream << std::fixed << std::setprecision(2) << runned_time;
		Text run_time;
		run_time.setFont(f);
		run_time.setCharacterSize(10);
		run_time.setFillColor(fillColor);
		run_time.setString(stream.str());
		run_time.setPosition(100, 26);
		run_time.setOutlineColor({ 0,0,0 });
		run_time.setOutlineThickness(3);

		// Số điểm
		Text num_score;
		num_score.setFont(f);
		num_score.setCharacterSize(10);
		num_score.setFillColor(fillColor);
		num_score.setString(to_string(tetris.score));
		num_score.setPosition(88, 26);
		num_score.setOutlineColor({ 0,0,0 });
		num_score.setOutlineThickness(3);


		// draw
		gameWindow.draw(run_time);
		gameWindow.draw(num_score);
		gameWindow.draw(nextBlock);
		gameWindow.draw(score);
		gameWindow.draw(speed);

		// Vẽ block kế tiếp
		tetris.draw_next_block(gameWindow);
		gameWindow.display();
	}
}

int main()
{
    const int cell = 8; // Adjust the cell size if needed
    const int column = 10; // Adjust the number of columns
    const int row = 20; // Adjust the number of rows
    const float screen_size = 1.0f;

	std::string playerName = "";
	RenderWindow window(VideoMode(800, 900), "Tetris");

	Texture t3, t4, t5, t6, t9;

	t3.loadFromFile("fontPic/Email.png");
	t4.loadFromFile("fontPic/Password.png");
	t5.loadFromFile("fontPic/Submit.png");
	t6.loadFromFile("fontPic/Back.png");
	t9.loadFromFile("fontPic/LoginOk.png");
	Sprite Email(t3);
	Sprite Password(t4);
	Sprite Submit(t5);
	Sprite Back(t6);
	Sprite LoginOK(t9);

	Font arial;
	arial.loadFromFile("fontPic/Arial.ttf");

	Textbox textLoginEmail(30, Color::White, false);
	textLoginEmail.setFont(arial);
	Textbox textLoginPassword(30, Color::White, false);
	textLoginPassword.setFont(arial);
	Textbox textRegisterEmail(30, Color::White, false);
	textRegisterEmail.setFont(arial);
	Textbox textRegisterConfirmEmail(30, Color::White, false);
	textRegisterConfirmEmail.setFont(arial);
	Textbox textRegisterPassword(30, Color::White, false);
	textRegisterPassword.setFont(arial);
	Textbox textRegisterConfirmPassword(30, Color::White, false);
	textRegisterConfirmPassword.setFont(arial);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("fontPic/home.png")) {
        std::cerr << "Error loading background texture" << std::endl;
        return 1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(810) / backgroundTexture.getSize().x, static_cast<float>(900) / backgroundTexture.getSize().y);
    backgroundSprite.setPosition(-5, -5);

    input();

    std::ofstream fout("data.txt", std::ios::in | std::ios::out);

	while (window.isOpen())
	{

		if (first == true)
		{
			for (int j = 1; j < i; j++)
			{
				fout << acc[j].email << "\n";
				fout << acc[j].password << "\n";
			}
			first = false;
		}
		Event e;
		string new_mail, new_password;

		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					int x = Mouse::getPosition(window).x;
					int y = Mouse::getPosition(window).y;
					if (scene == 1)
					{
						if (x >= 170 && x <= 640 && y >= 470 && y <= 560)
						{
							// START
							playGame(fout, cell, column, row,screen_size);
						}
						if (x >= 233 && x <= 583 && y >= 607 && y <= 667)
						{
							// LOGIN
							scene = 2;
						}
						if (x >= 233 && x <= 583 && y >= 700 && y <= 760)
						{
							// REGISTER
							scene = 3;
						}
						if (x >= 720 && x <= 780 && y >= 17 && y <= 52)
						{
							// SETTING
							cout << "setting" << endl;
						}
					}
					if (scene == 2)
					{
						// back
						if (x >= 275 && x <= 510 && y >= 540 && y <= 610)
						{
							scene = 1;
						}
						if (x >= 22 && x <= 722 && y >= 71 && y <= 141)
						{
							// click on email
							scene2.email = true;
							textLoginEmail.setSelected(true);
						}
						if (x >= 22 && x <= 722 && y >= 225 && y <= 295)
						{
							//click on password
							scene2.password = true;
							textLoginPassword.setSelected(true);
						}
						// submit
						if (x >= 230 && x <= 560 && y >= 405 && y <= 511)
						{
							std::string e, p;
							e = textLoginEmail.getText();
							p = textLoginPassword.getText();
							if (e.empty() == false && p.empty() == false)
							{
								for (int j = 1; j <= i; j++)
								{
									if (e == acc[j].email && p == acc[j].password)
									{
										playerName = e;
										scene = 4;
									}
								}
							}
						}
					}
					if (scene == 3)
					{
						// back
						if (x >= 275 && x <= 510 && y >= 640 && y <= 710)
						{
							scene = 1;
						}
						// email
						if (x >= 15 && x <= 715 && y >= 55 && y <= 125)
						{
							scene3.email = true;
							textRegisterEmail.setSelected(true);
						}
						// password
						if (x >= 15 && x <= 715 && y >= 198 && y <= 268)
						{
							scene3.password = true;
							textRegisterPassword.setSelected(true);
						}
						// confirm password
						if (x >= 15 && x <= 715 && y >= 340 && y <= 410)
						{
							scene3.confirmPassword = true;
							textRegisterConfirmPassword.setSelected(true);
						}
						//submit
						if (x >= 230 && x <= 560 && y >= 505 && y <= 610)
						{
							std::string e, p, cp;
							e = textRegisterEmail.getText();
							p = textRegisterPassword.getText();
							cp = textRegisterConfirmPassword.getText();
							if (e.empty() == false && p.empty() == false && cp.empty() == false)
							{
								if (p == cp)
								{
									fout << e << "\n";
									fout << p << "\n";
								}
							}
						}
					}
					if (scene == 4) {
						if (x >= 300 && x <= 500 && y >= 400 && y <= 500) {
							playGame(fout,cell,column,row, screen_size);
						}
					}
				}
			}
			if (e.type == Event::TextEntered)
			{
				if (scene == 2)
				{
					if (scene2.email == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textLoginEmail.setSelected(false);
							scene2.email = false;
						}
						else
						{
							textLoginEmail.typedOn(e);
						}
					}
					else if (scene2.password == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textLoginPassword.setSelected(false);
							scene2.password = false;
						}
						else
						{
							textLoginPassword.typedOn(e);
						}
					}
				}
				if (scene == 3)
				{
					if (scene3.email == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterEmail.setSelected(false);
							scene3.email = false;
						}
						else
						{
							textRegisterEmail.typedOn(e);
						}
					}
					else if (scene3.confirmEmail == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterConfirmEmail.setSelected(false);
							scene3.confirmEmail = false;
						}
						else
						{
							textRegisterConfirmEmail.typedOn(e);
						}
					}
					else if (scene3.password == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterPassword.setSelected(false);
							scene3.password = false;
						}
						else
						{
							textRegisterPassword.typedOn(e);
						}
					}
					else if (scene3.confirmPassword == true)
					{
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							textRegisterConfirmPassword.setSelected(false);
							scene3.confirmPassword = false;
						}
						else
						{
							textRegisterConfirmPassword.typedOn(e);
						}
					}
				}
			}
		}
		window.draw(backgroundSprite);
		if (scene == 1)
		{
			draw_home_without_login(window, backgroundTexture);
		}
		if (scene == 2)
		{
			draw_login_interface(window, Back,Submit,Email,Password);
			textLoginEmail.setPosition({ 210,76 });
			textLoginEmail.drawTo(window);
			textLoginPassword.setPosition({ 269,237 });
			textLoginPassword.drawTo(window);

		}
		if (scene == 3)
		{
			draw_register_interface(window, Back, Submit, Email, Password);
			textRegisterEmail.setPosition({ 200, 70 });
			textRegisterEmail.drawTo(window);
			textRegisterPassword.setPosition({ 300,210 });
			textRegisterPassword.drawTo(window);
			textRegisterConfirmPassword.setPosition({ 300,350 });
			textRegisterConfirmPassword.drawTo(window);
		}
		if (scene == 4)
		{
			draw_home_with_login(window, backgroundTexture, playerName);
		}
		window.display();
	}
    window.close();
    return 0;
}
