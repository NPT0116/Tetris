#pragma once
#include "Block_Type.cpp"
#include "Headers/Position.h"
#include <vector>
#include <time.h>
using namespace std;
class Tetris
{
private:
    Block currBlock;
    Block nextBlock;
public:
    GameBox game;
    vector <Block>blocks;
    vector <Block>get_all_type_block();
    Tetris();
    //trả về địa chỉ của 1 block.
    Block randomBlock();
    void hand_input(Event &event);
    void moveBlockLeft();
    void moveBlockRight();
    void moveBlockDown();
    void Draw(RenderWindow &window);
    void moveBlockSpace();
};

