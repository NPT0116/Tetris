#include "Tetris.h"
using namespace sf;

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

void drawObjects(RenderWindow& window, Tetris& tetris, Sprite& backgroundSprite, RectangleShape& recBack,
    RectangleShape& recNext, RectangleShape& recScore, RectangleShape& recSpeed,
    RectangleShape& recNextShadow, RectangleShape& recScoreShadow, RectangleShape& recSpeedShadow,
    Text& nextBlock, Text& score, Text& speed)
{
    window.clear(Color(0, 0, 0));
    window.draw(backgroundSprite);
    window.draw(recBack);

    tetris.Draw(window);

    window.draw(recNextShadow);
    window.draw(recScoreShadow);
    window.draw(recSpeedShadow);
    window.draw(recNext);
    window.draw(recScore);
    window.draw(recSpeed);

    window.draw(nextBlock);
    window.draw(score);
    window.draw(speed);

    window.display();
}

int main()
{
    //size
   /* unsigned char row = 20;
    unsigned char column = 10;
    unsigned char cell = 8;
    unsigned char screen_size = 4;
    unsigned char frame = 16667;*/

    const int cell = 30; // Adjust the cell size if needed
    const int column = 10; // Adjust the number of columns
    const int row = 20; // Adjust the number of rows
    const float screen_size = 1.0f;

    //text
    string font = "resoure/CallOfOpsDutyIi-7Bgm4.ttf";
    sf::Font f; int characterSize = 10; sf::Color fillColor = sf::Color::White;
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
    

    //Game
    Tetris tetris;

    RenderWindow window(VideoMode(/*cell * column * screen_size * 2.6*/800, /*cell * row * screen_size * 1.4*/900), "Tetris", Style::Close);
    window.setView(View(FloatRect(-3, -2, 140, 165)));

    RectangleShape cellShape(Vector2f(cell - 1, cell - 1));
    cellShape.setFillColor(Color(36, 36, 88));

    //background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("D:/tetris/tetris/resoure/new.jpg")) {
        std::cerr << "Error loading background texture" << std::endl;
        return 1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(400) / backgroundTexture.getSize().x, static_cast<float>(170) / backgroundTexture.getSize().y);
    backgroundSprite.setPosition(-5, -5);

    //dropping
    sf::Clock clock;
    float elapsedTime = 0.0f;
    float interval = 0.5f; // 1 second interval
    window.clear(Color(0, 0, 0));

    //shapes
    sf::RectangleShape recScore = createRectangleShape(40, 20, 88, 26, sf::Color(39, 139, 75));
    sf::RectangleShape recScoreShadow = createRectangleShape(40, 20, 90, 28, sf::Color(11, 66, 35));
    sf::RectangleShape recSpeed = createRectangleShape(40, 20, 88, 70, sf::Color(173, 7, 31));
    sf::RectangleShape recSpeedShadow = createRectangleShape(40, 20, 90, 72, sf::Color(60, 0, 0));
    sf::RectangleShape recNext = createRectangleShape(40, 40, 88, 116, sf::Color(6, 171, 165));
    sf::RectangleShape recNextShadow = createRectangleShape(40, 40, 90, 118, sf::Color(0, 72, 78));
    sf::RectangleShape recBack = createRectangleShape(81, 161, 0, 0, sf::Color(30, 6, 64));


    while (window.isOpen())
    {
        Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                tetris.hand_input(event);
            }
        }
        if (trigger_event(clock, elapsedTime, interval))
        {
            tetris.moveBlockDown();
        }
        {
            window.clear(Color(0, 0, 0));
            //cout << "clear" << endl;
        }
        window.draw(backgroundSprite);
        window.draw(recBack);

        {
            tetris.Draw(window);
            //cout << "draw" << endl;
        }
        //rec
        window.draw(recNextShadow);
        window.draw(recScoreShadow);
        window.draw(recSpeedShadow);
        window.draw(recNext);
        window.draw(recScore);
        window.draw(recSpeed);
        //text
        window.draw(nextBlock);
        window.draw(score);
        window.draw(speed);
        window.display();
    }
    window.close();
    return 0;
}