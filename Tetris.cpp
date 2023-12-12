#include "Tetris.h"


vector <Block> Tetris :: get_all_type_block()
{
    return {L_block(), J_block(), I_block(), O_block(), S_block(),T_block(), Z_block() };
}



Tetris :: Tetris ()
{
    blocks = {L_block(), J_block(), I_block(), O_block(), S_block(),T_block(), Z_block() };
    game.innit();
    currBlock = randomBlock();
    nextBlock = randomBlock();
}

Block  Tetris:: randomBlock()
{
    if (blocks.empty())
    {
        blocks = {L_block(), J_block(), I_block(), O_block(), S_block(),T_block(), Z_block() };
    }
    srand(time (NULL));
    rand();
    int index = rand() % blocks.size();

    Block randBlock = blocks[index];
    blocks.erase(blocks.begin() + index);
    return  randBlock;
}


void Tetris ::  hand_input(Event &event)
{
    switch (event.key.code)
    {
    case Keyboard::Left:
        moveBlockLeft();
        break;
    case Keyboard::Right:
        moveBlockRight();
        break;
    case Keyboard::Down:
        moveBlockDown();
        break;
    // case Keyboard::Space:
    //     moveBlockSpace();
    //     break;
    default:
        break;
    }
}

void Tetris:: moveBlockLeft()
{
    currBlock.move(0,-1);
}

void Tetris::moveBlockRight()
{
    currBlock.move(0,1);
}
void Tetris :: moveBlockDown ()
{
    currBlock.move(1,0);
}

void Tetris :: Draw(RenderWindow &window)
{
    game.draw_cell(window);
    currBlock.draw(window);
}