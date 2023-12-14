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

    RenderWindow window(VideoMode(/*cell * column * screen_size * 2.6*/600, /*cell * row * screen_size * 1.4*/700), "Tetris", Style::Close);
    window.setView(View(FloatRect(-3, -2, 140, 165)));

    RectangleShape cellShape(Vector2f(cell - 1, cell - 1));
    cellShape.setFillColor(Color(36, 36, 88));

    //background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("resoure/test.jpg")) {
        std::cerr << "Error loading background texture" << std::endl;
        return 1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(400) / backgroundTexture.getSize().x, static_cast<float>(170) / backgroundTexture.getSize().y);
    backgroundSprite.setPosition(-5, -5);

    //dropping

    window.clear(Color(0, 0, 0));

    //shapes
    sf::RectangleShape recScore = createRectangleShape(40, 20, 88, 26, sf::Color(39, 139, 75));
    sf::RectangleShape recScoreShadow = createRectangleShape(40, 20, 90, 28, sf::Color(11, 66, 35));
    sf::RectangleShape recSpeed = createRectangleShape(40, 20, 88, 70, sf::Color(173, 7, 31));
    sf::RectangleShape recSpeedShadow = createRectangleShape(40, 20, 90, 72, sf::Color(60, 0, 0));
    sf::RectangleShape recNext = createRectangleShape(40, 40, 88, 116, sf::Color(6, 171, 165));
    sf::RectangleShape recNextShadow = createRectangleShape(40, 40, 90, 118, sf::Color(0, 72, 78));
    sf::RectangleShape recBack = createRectangleShape(81, 161, 0, 0, sf::Color(30, 6, 64));

    // Thời gian
     
    while (window.isOpen())
    {
        window.setFramerateLimit(20000); 
        Event event;
        tetris.Drop_ghost_block(); 
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                tetris.hand_input(event, window);
            }
        }
        if (tetris.drop_block == true)
        {

            tetris.moveBlockDown(window);
        }
        if (trigger_event(tetris.clock_event, tetris.elapsedTime, tetris.interval))
        {
            tetris.moveBlockDown(window);
        }
        {
            window.clear(Color(0, 0, 0));
            //cout << "clear" << endl;
        }
        window.draw(backgroundSprite);
        window.draw(recBack);


        tetris.Draw(window);
        //rec
        window.draw(recNextShadow);
        window.draw(recScoreShadow);
        window.draw(recSpeedShadow);
        window.draw(recNext);
        window.draw(recScore);
        window.draw(recSpeed);
        //text
        // Thời gian và tăng tốc độ
        if (!tetris.gameOver) {
            tetris.end = clock();
         }
        float runned_time = (float)(tetris.end - tetris.begin)/CLOCKS_PER_SEC;
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
        window.draw(run_time); 
        window.draw(num_score);
        window.draw(nextBlock);
        window.draw(score);
        window.draw(speed);

        // Vẽ block kế tiếp
        tetris.draw_next_block(window);
        window.display();
        
    }
    window.close();
    return 0;
}
