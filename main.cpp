
#include "Tetris.h"
using namespace sf;
int main()
{
    unsigned char row = 20;
    unsigned char column = 10;
    unsigned char cell = 8;
    unsigned char screen_size = 4;
    unsigned char frame = 16667;

    Tetris tetris;

    RenderWindow window(VideoMode(cell * column * screen_size, cell * row * screen_size), "Tetris", Style::Close);
    window.setView(View(FloatRect(0, 0,  cell * column, cell * row)));

    RectangleShape cellShape(Vector2f(cell - 1, cell - 1));
    cellShape.setFillColor(Color(36, 36, 88));
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
        {

        window.clear(Color(0,0,0));
        cout<<"clear"<<endl;
        }
        {
        tetris.Draw(window);
        cout<<"draw"<<endl;
        }
        window.display();
    }
    window.close();
    return 0;
}
