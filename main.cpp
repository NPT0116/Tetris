#include "Tetris.h"
using namespace sf;

bool trigger_event(Clock &clock, float &elapsedTime, float interval)
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

int main()
{
    unsigned char row = 20;
    unsigned char column = 10;
    unsigned char cell = 8;
    unsigned char screen_size = 4;

    Tetris tetris;

    RenderWindow window(VideoMode(cell * column * screen_size, cell * row * screen_size), "Tetris", Style::Close);
    window.setView(View(FloatRect(0, 0, cell * column, cell * row)));
    window.setFramerateLimit(120);

    RectangleShape cellShape(Vector2f(cell - 1, cell - 1));
    cellShape.setFillColor(Color(36, 36, 88));

    sf::Clock clock;
    float elapsedTime = 0.0f;
    float interval = 0.2f; // 1 second interval
    window.clear(Color(0, 0, 0));
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
            if (tetris.gameOver && event.type == Event::KeyPressed)
            {
                tetris.gameOver = false;
                tetris.restart_game();
            }
        }

        if (trigger_event(clock, elapsedTime, interval))
        {
            tetris.moveBlockDown();
        }
        tetris.box.display();
        tetris.Draw(window);
        window.display();
    }

    window.close();
    return 0;
}
