#include "Tetris.h"


vector <Block> Tetris :: get_all_type_block()
{
    return {L_block(), J_block(), I_block(), O_block(), S_block(),T_block(), Z_block() };
}



Tetris :: Tetris ()
{
    blocks = {L_block(), J_block(), I_block(), O_block(), S_block(),T_block(), Z_block() };
    box.innit();
    currBlock = randomBlock();
    nextBlock = randomBlock();
    ghost_Block = currBlock; 
    ghost_Block.id = 9;
    elapsedTime = 0.0f;
    interval = 0.5f;
    // Nhạc game
    game_sound.openFromFile("resoure/back_ground_sound.mp3");
    game_sound.setVolume(60); 
    game_sound.play();
    flip_sound.openFromFile("resoure/Flip_sound.MP3");
    clear_sound.openFromFile("resoure/Clear_sound.MP3");
    drop_sound.openFromFile("resoure/drop_sound.MP3");
    end_sound.openFromFile("resoure/end_sound.MP3");
    flip_sound.setVolume(60); 
    // Thời gian
    begin = clock(); 
}

Tetris::~Tetris() {
    game_sound.stop();
    flip_sound.stop();
    clear_sound.stop();
    drop_sound.stop();
    end_sound.stop(); 
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


void Tetris ::  hand_input(Event &event, RenderWindow& window)
{
    // xem coi sự kiện có phải là keypress không
    flip_sound.play();
        switch (event.key.code)
        {
            
        case Keyboard::Left:
            moveBlockLeft();
            Update_ghost_block();
            break;
        case Keyboard::Right:
            moveBlockRight();
            Update_ghost_block();
            break;
        case Keyboard::Down:
            moveBlockDown(window);
            break;
        case Keyboard:: Up:
            rotate_block();
            Update_ghost_block();
            rotate_block(true); 
            break;
        case Keyboard::Space:
            drop_block = true;
            drop_sound.play();
        default:
            break;
        }  
     
}

void Tetris:: moveBlockLeft()
{
    if (!gameOver)
    {
    currBlock.move(0,-1); 
    if (is_block_outside()||!is_block_fit())
    {
    currBlock.move(0,1);
    }
    }
}

void Tetris::moveBlockRight()
{
    if (!gameOver)
    {
    currBlock.move(0,1);
    if (is_block_outside() || !is_block_fit())
    {
    currBlock.move(0,-1); 
    }
    }
}



void Tetris::Update_ghost_block() {
    vector <Position> pos = ghost_Block.get_curr_position();
    for (Position po : pos)
    {
        box.box[po.row][po.col] = 9;
    }
    ghost_Block.row_margin = currBlock.row_margin;
    ghost_Block.col_margin = currBlock.col_margin;
    ghost_Block.id = 9; 
}


void Tetris::Drop_ghost_block() {
    if (!gameOver)
    {
        ghost_Block.move(1, 0);
        if (is_block_outside(true) || !is_block_fit(true))
        {
            ghost_Block.move(-1, 0);
            lock_ghost_block();
        }
    }
    else {
        game_sound.stop();
    }
}

void Tetris :: moveBlockDown (RenderWindow& window)
{
    if (!gameOver)
    {
        currBlock.move(1,0);
    if (is_block_outside() || !is_block_fit())
    {
        currBlock.move(-1,0);
        lock_block(window);//////chặn block lại ko cho dịch qua trái phải khi chạm đáy
        }
    }
    else {
        game_sound.stop();
    }
}

void Tetris :: Draw(RenderWindow &window)
{
    box.draw_cell(window);
    ghost_Block.draw(window, 0, 0);
    currBlock.draw(window, 0 , 0);
    
}

void Tetris::draw_next_block(RenderWindow& window) {
    switch (nextBlock.id) {
    case 3:
        nextBlock.draw(window, 75, 110);
    case 4:
        nextBlock.draw(window, 75, 110);
    default:
        nextBlock.draw(window, 75, 110);
        break;
    }
}

bool Tetris::is_block_outside(bool check_ghost)
{
    if (!check_ghost) {
        vector <Position > pos = currBlock.get_curr_position();
        for (Position po : pos)
        {
            if (box.is_cell_outside_box(po.row, po.col))
            {
                return 1;
            }
        }
        return 0;
    }
    else {
        vector <Position > pos = ghost_Block.get_curr_position();
        for (Position po : pos)
        {
            if (box.is_cell_outside_box(po.row, po.col))
            {
                return 1;
            }
        }
        return 0;
    }
}
void Tetris :: rotate_block (bool check_ghost_block)
{
    if (!check_ghost_block) {
        currBlock.rotate_block();
        if (is_block_outside() || !is_block_fit())
        {
            currBlock.rotate_block();
            currBlock.rotate_block();
            currBlock.rotate_block();
        }
    }
    else {
        ghost_Block.rotate_block();
        if (is_block_outside(true) || !is_block_fit(true))
        {
            ghost_Block.rotate_block();
            ghost_Block.rotate_block();
            ghost_Block.rotate_block();
        }
    }
    
}

void Tetris::lock_ghost_block() {
    vector <Position> pos = ghost_Block.get_curr_position();
    ghost_Block.id = 7; 
    for (Position po : pos)
    {
        box.box[po.row][po.col] = ghost_Block.id;
    }
}

void Tetris :: lock_block(RenderWindow& window)
{
    vector <Position> pos = currBlock.get_curr_position();

    for (Position po : pos)
    {
        box.box[po.row][po.col] = currBlock.id;
    }
    currBlock = nextBlock;
    // Chỉnh lại ghost_block khi curr đổi
    ghost_Block = currBlock;
    ghost_Block.id = 7; 
    if (!is_block_fit())
    {
        currBlock.id = 7;
        end_sound.play();
        //set lại id block current  vì end game rồi và mình muốn chuyển cả block hiện tại này có giá trị là xám grey có id là 7
        game_over();
    }
    if (drop_block== true)
    {
       drop_block = false;
    }
    nextBlock = randomBlock();
    int row_cleared = box.update_box(window);
    if (row_cleared > 0) {
        UpdateScore(row_cleared, 0);
        cout << "yes" << endl; 
        interval *= 0.95;
    }
}   

bool Tetris :: is_block_fit(bool check_ghost)
{
    if (!check_ghost) {
        vector <Position>pos = currBlock.get_curr_position();
        for (Position po : pos)
        {
            if (box.is_empty_cell(po.row, po.col) == false)
            {
                return false;
            }
        }
        return true;
    }
    else {
        vector <Position>pos = ghost_Block.get_curr_position();
        for (Position po : pos)
        {
            if (box.is_empty_cell(po.row, po.col) == false)
            {
                return false;
            }
        }
        return true;
    }
    
}


void Tetris :: game_over()
{
    gameOver = true;
    box.game_over();
}



void Tetris ::  restart_game()
{
    box.innit();
    blocks = get_all_type_block();
    currBlock = randomBlock();
    nextBlock = randomBlock();
    score = 0; 
}

void Tetris::UpdateScore(int LinesCleared, int moveDownPoint) {
    clear_sound.play();
     
    switch (LinesCleared)
    {  
    case 1:
        score += 100; 
        break; 
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 700;
        break; 
    default:
        break;
    }
    score += moveDownPoint;
}
