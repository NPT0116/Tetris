#include "Tetris.h"
vector <Block> Tetris::get_all_type_block()
{
    return { L_block(), J_block(), I_block(), O_block(), S_block(),T_block(), Z_block() };
}



Tetris::Tetris()
{
    score = 0;
    wait_for_fill = 0;
    skill_list.push_back(-1);
    skill_list.push_back(-1);
    skill_list.push_back(-1);
    skill_list.push_back(-1);
    count_score = 500;
    blocks = { L_block(), J_block(), I_block(), O_block(), S_block(),T_block(), Z_block() };
    box.innit();
    currBlock = randomBlock();
    nextBlock = randomBlock();
    ghost_Block = currBlock;
    ghost_Block.id = 12;
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
    denied_sound.openFromFile("resoure/Skill/Denied_sound.MP3");
    disapear_sound.openFromFile("resoure/Skill/Disapear_sound.MP3");
    // Thời gian
    begin = clock();
    speed = 100;
    // Skill
    Next_skill = 0;
    temp_int = false;
}

Tetris::~Tetris() {
    game_sound.stop();
    flip_sound.stop();
    clear_sound.stop();
    drop_sound.stop();
    end_sound.stop();
    denied_sound.stop();
    disapear_sound.stop();
}

Block  Tetris::randomBlock()
{
    if (blocks.empty())
    {
        blocks = { L_block(), J_block(), I_block(), O_block(), S_block(),T_block(), Z_block() };
    }
    srand(time(NULL));
    rand();
    int index = rand() % blocks.size();

    Block randBlock = blocks[index];
    blocks.erase(blocks.begin() + index);
    return  randBlock;

}


void Tetris::hand_input(Event& event, RenderWindow& window)
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
    case Keyboard::Up:
        rotate_block();
        Update_ghost_block();
        rotate_block(true);
        break;
    case Keyboard::Space:
        drop_block = true;
        drop_sound.play();
        break;
    case Keyboard::Q:
        Boom_block(window);
        break;
    case Keyboard::W:
        Slow_speed(window);
        break;
    case Keyboard::E:
        Clear_row(window);
        break;
    case Keyboard::R:
        Pick_Block(window);
        break;
    default:
        break;
    }

}

void Tetris::moveBlockLeft()
{
    if (!gameOver)
    {
        currBlock.move(0, -1);
        if (is_block_outside() || !is_block_fit())
        {
            currBlock.move(0, 1);
        }
    }
}

void Tetris::moveBlockRight()
{
    if (!gameOver)
    {
        currBlock.move(0, 1);
        if (is_block_outside() || !is_block_fit())
        {
            currBlock.move(0, -1);
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

void Tetris::moveBlockDown(RenderWindow& window)
{
    if (!gameOver)
    {
        currBlock.move(1, 0);
        if (is_block_outside() || !is_block_fit())
        {
            currBlock.move(-1, 0);
            lock_block(window);//////chặn block lại ko cho dịch qua trái phải khi chạm đáy
        }
    }
    else {
        game_sound.stop();
    }
}

void Tetris::Draw(RenderWindow& window)
{
    box.draw_cell(window);
    ghost_Block.draw(window, 0, 0);
    currBlock.draw(window, 0, 0);

}

void Tetris::draw_next_block(RenderWindow& window) {
    if (nextBlock.id == 2) {
        nextBlock.draw(window, 73 - 5, 130);
    }
    else if (nextBlock.id == 3) {
        nextBlock.draw(window, 73 + 3, 130);
    }
    else {
        nextBlock.draw(window, 73, 130);
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
void Tetris::rotate_block(bool check_ghost_block)
{
    if (!check_ghost_block) {
        currBlock.rotate_block();
        if (is_block_outside() || !is_block_fit())
        {
            if (currBlock.id == 2) {
                currBlock.move(0, 2);
                if (is_block_outside() || !is_block_fit()) {
                    currBlock.move(0, -4);
                    if (is_block_outside() || !is_block_fit()) {
                        currBlock.move(0, 2);
                        currBlock.rotate_block();
                        currBlock.rotate_block();
                        currBlock.rotate_block();
                    }
                }
            }
            else {
                currBlock.move(0, 1);
                if (is_block_outside() || !is_block_fit()) {
                    currBlock.move(0, -2);
                    if (is_block_outside() || !is_block_fit()) {
                        currBlock.move(0, 1);
                        currBlock.rotate_block();
                        currBlock.rotate_block();
                        currBlock.rotate_block();
                    }
                }
            }
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
    ghost_Block.id = 12;
    for (Position po : pos)
    {
        box.box[po.row][po.col] = 7;
    }
}

void Tetris::lock_block(RenderWindow& window)
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
    if (drop_block == true)
    {
        drop_block = false;
    }
    nextBlock = randomBlock();
    int row_cleared = box.update_box(window);
    if (row_cleared > 0) {
        UpdateScore(row_cleared, 0);
        cout << "yes" << endl;
    }
}



bool Tetris::is_block_fit(bool check_ghost)
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


void Tetris::game_over()
{
    gameOver = true;
    box.game_over();
}



void Tetris::restart_game()
{
    box.innit();
    blocks = get_all_type_block();
    currBlock = randomBlock();
    nextBlock = randomBlock();
    score = 0;
}

void Tetris::UpdateScore(int LinesCleared, int moveDownPoint) {
    clear_sound.play();
    if (temp_int) {
        cout << interval << endl;
        interval = interval / 10.0;
        cout << interval << endl;
        temp_int = false;
    }
    switch (LinesCleared)
    {
    case 1:
        speed *= 101.0 / 100.0;
        interval *= 0.99;
        score += 100;
        break;
    case 2:
        speed *= 103.0 / 100.0;
        interval *= 0.97;
        score += 300;
        break;
    case 3:
        speed *= 105.0 / 100.0;
        interval *= 0.95;
        score += 500;
        break;
    case 4:
        speed *= 107.0 / 100.0;
        interval *= 0.93;
        score += 700;
        break;
    default:
        break;
    }
    score += moveDownPoint;
    if (score > count_score) {
        skill_list[wait_for_fill] = Next_skill;
        count_score += 500;
        wait_for_fill += 1;
        wait_for_fill = wait_for_fill % 4;
        Random_Next_skill();
    }
}

void Tetris::Random_Next_skill() {
    srand(time(NULL));
    // generate secret number between 1 and 10
    Next_skill = rand() % 4;
}

void Tetris::Draw_next_skill(RenderWindow& window) {
    if (Next_skill == 0) {
        sf::Texture BoomBLock;
        if (!BoomBLock.loadFromFile("resoure/Skill/BoomBlock.png")) {
            // Handle error if the image fails to load
            cout << "Cant not load image" << endl;
        }
        // Create a sprite and set its texture
        sf::Sprite BoomBLock_sprite;
        BoomBLock_sprite.setTexture(BoomBLock);
        BoomBLock_sprite.setPosition(15, 120);
        BoomBLock_sprite.setScale(0.2, 0.2);
        window.draw(BoomBLock_sprite);
    }
    else if (Next_skill == 1) {
        sf::Texture SlowSpeed;
        if (!SlowSpeed.loadFromFile("resoure/Skill/SlowSpeed.png")) {
            // Handle error if the image fails to load
            cout << "Cant not load image" << endl;
        }

        // Create a sprite and set its texture
        sf::Sprite SlowSpeed_sprite;
        SlowSpeed_sprite.setTexture(SlowSpeed);
        SlowSpeed_sprite.setPosition(15, 120);
        SlowSpeed_sprite.setScale(0.2, 0.2);
        window.draw(SlowSpeed_sprite);
    }
    else if (Next_skill == 2) {
        sf::Texture ClearRow;
        if (!ClearRow.loadFromFile("resoure/Skill/ClearRow.png")) {
            // Handle error if the image fails to load
            cout << "Cant not load image" << endl;
        }

        // Create a sprite and set its texture
        sf::Sprite ClearRow_sprite;
        ClearRow_sprite.setTexture(ClearRow);
        ClearRow_sprite.setPosition(15, 120);
        ClearRow_sprite.setScale(0.2, 0.2);
        window.draw(ClearRow_sprite);
    }
    else if (Next_skill == 3) {
        sf::Texture PickBlock;
        if (!PickBlock.loadFromFile("resoure/Skill/PickBlock.png")) {
            // Handle error if the image fails to load
            cout << "Cant not load image" << endl;
        }

        // Create a sprite and set its texture
        sf::Sprite PickBlock_sprite;
        PickBlock_sprite.setTexture(PickBlock);
        PickBlock_sprite.setPosition(15, 120);
        PickBlock_sprite.setScale(0.2, 0.2);
        window.draw(PickBlock_sprite);
    }
    else {};
}

void Tetris::Count_skill(int& bb, int& cr, int& sp, int& pb) {
    for (int i = 0; i < 4; i++) {
        if (skill_list[i] == 0) {
            bb++;
        }
        else if (skill_list[i] == 1) {
            sp++;
        }
        else if (skill_list[i] == 2) {
            cr++;
        }
        else if (skill_list[i] == 3) {
            pb++;
        }
        else {};
    }
}

void Tetris::Draw_count_skill(RenderWindow& window) {
    Font f;
    f.loadFromFile("resoure/CallOfOpsDutyIi-7Bgm4.ttf");
    int bb = 0, cr = 0, sp = 0, pb = 0;
    Count_skill(bb, cr, sp, pb);
    Text count_skill;
    count_skill.setFont(f);
    count_skill.setCharacterSize(10);
    count_skill.setFillColor(Color(239, 207, 38));
    count_skill.setString(to_string(bb) + '\n' + to_string(sp) + '\n' + to_string(cr) + '\n' + to_string(pb));
    count_skill.setPosition(55, 90 + 105);
    count_skill.setOutlineThickness(0.5);
    window.draw(count_skill);
}

bool  Tetris::skill_list_check(int n) {
    for (int i = 0; i < 4; i++) {
        if (skill_list[i] == n) {
            wait_for_fill = i;
            skill_list[i] = -1;
            return true;
        }
    }
    return false;
}

void Tetris::Boom_block(RenderWindow& window) {
    if (skill_list_check(0)) {
        vector <Position> pos = currBlock.get_curr_position();

        for (Position po : pos)
        {
            box.box[po.row][po.col] = 10;
        }
        disapear_sound.play();
        for (int i = 0; i < 20; i++) {
            box.draw_cell(window);
            window.display();
            sleep(seconds(0.01));
            for (Position po : pos)
            {
                box.box[po.row][po.col] = 9;
            }
        }

        currBlock = nextBlock;
        Update_ghost_block();
        ghost_Block = currBlock;
        ghost_Block.id = 7;
        nextBlock = randomBlock();
        box.update_box(window);
    }
    else {
        denied_sound.play();
    }
}


void Tetris::Slow_speed(RenderWindow& window) {
    if (skill_list_check(1)) {
        sf::Texture slowspeed;
        if (!slowspeed.loadFromFile("resoure/Skill/Down_speed.png")) {
            cout << "Cant not load image" << endl;
        }
        interval *= 10;
        temp_int = true;
        // Create a sprite and set its texture
        sf::Sprite SlowSpeed_sprite;
        SlowSpeed_sprite.setTexture(slowspeed);
        SlowSpeed_sprite.setPosition(170, 155);
        SlowSpeed_sprite.setScale(0.07, 0.07);
        window.draw(SlowSpeed_sprite);
        window.display();
        disapear_sound.play();
        sleep(seconds(0.2));
    }
    else {
        denied_sound.play();
    }
}

void Tetris::Clear_row(RenderWindow& window) {
    // Vẽ khung
    if (skill_list_check(2)) {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(1000, 1000));
        rectangle.setPosition(-1, -1);
        rectangle.setFillColor(Color(0, 0, 0, 200));
        window.draw(rectangle);
        sf::Texture Rec_cr;
        if (!Rec_cr.loadFromFile("resoure/Skill/Rec_cr.png")) {
            cout << "Cant not load image" << endl;
        }
        // Create a sprite and set its texture
        sf::Sprite RecCr_sprite;
        RecCr_sprite.setTexture(Rec_cr);
        RecCr_sprite.setPosition(50, 85);
        RecCr_sprite.setScale(0.25, 0.25);
        box.draw_cell(window);
        window.draw(RecCr_sprite);
        window.display();
        Event event;
        clock_t start = clock();
        int row_delete = -1;
        do {
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    switch (event.key.code)
                    {

                    case Keyboard::Num1:
                        row_delete = 1;
                        break;
                    case Keyboard::Num2:
                        row_delete = 2;
                        break;
                    case Keyboard::Num3:
                        row_delete = 3;
                        break;
                    case Keyboard::Num4:
                        row_delete = 4;
                        break;
                    case Keyboard::Num5:
                        row_delete = 5;
                        break;
                    case Keyboard::Num6:
                        row_delete = 6;
                        break;
                    case Keyboard::Num7:
                        row_delete = 7;
                        break;
                    case Keyboard::Num8:
                        row_delete = 8;
                        break;
                    case Keyboard::Num9:
                        row_delete = 9;
                        break;
                    case Keyboard::Q:
                        row_delete = 10;
                        break;
                    case Keyboard::W:
                        row_delete = 11;
                        break;
                    case Keyboard::E:
                        row_delete = 12;
                        break;
                    case Keyboard::R:
                        row_delete = 13;
                        break;
                    case Keyboard::T:
                        row_delete = 14;
                        break;
                    case Keyboard::Y:
                        row_delete = 15;
                        break;
                    case Keyboard::U:
                        row_delete = 16;
                        break;
                    case Keyboard::I:
                        row_delete = 17;
                        break;
                    case Keyboard::O:
                        row_delete = 18;
                        break;
                    case Keyboard::P:
                        row_delete = 19;
                        break;
                    case Keyboard::A:
                        row_delete = 20;
                        break;
                    default:
                        break;
                    }
                }
            }
            clock_t end = clock();
            if (row_delete != -1) {
                clear_sound.play();
                row_delete = row_delete - 1;
                box.clear_row(row_delete);
                box.draw_cell(window);
                Update_ghost_block();
                for (int i = row_delete; i > 0; i--) {
                    window.display();
                    sleep(seconds(0.01f));
                    box.move_row(i -1, 1);
                }
                break;
            }
        } while ((end - start) / CLOCKS_PER_SEC <= 5);
    }
    else {
        denied_sound.play();
    }
}

void Tetris::Pick_Block(RenderWindow& window) {
    // Làm mờ màn hình
    if (skill_list_check(3)) {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(1000, 1000));
        rectangle.setPosition(-1, -1);
        rectangle.setFillColor(Color(0, 0, 0, 200));
        window.draw(rectangle);
        sf::Texture CB;
        if (!CB.loadFromFile("resoure/Skill/Choice_nb.jpg")) {
            cout << "Cant not load image" << endl;
        }
        // Create a sprite and set its texture
        sf::Sprite CB_sprite;
        CB_sprite.setTexture(CB);
        CB_sprite.setPosition(38, 50);
        CB_sprite.setScale(0.25, 0.25);
        window.draw(CB_sprite);

        // Chọn block
        L_block().draw(window, -60, 30);
        J_block().draw(window, 0, 30);
        I_block().draw(window, 60 - 2 + 3, 30);
        O_block().draw(window, -60 + 3, 80);
        S_block().draw(window, 0, 80);
        T_block().draw(window, 60 + 3, 80);
        Z_block().draw(window, -60, 130);
        window.display();
        bool exists = false;
        Event event;
        clock_t start = clock();
        int row_delete = -1;
        do {
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Event::KeyPressed)
                {
                    switch (event.key.code)
                    {
                    case Keyboard::Num1:
                        nextBlock = L_block();
                        exists = true;
                        break;
                    case Keyboard::Num2:

                        nextBlock = J_block();
                        exists = true;
                        break;
                    case Keyboard::Num3:
                        nextBlock = I_block();
                        exists = true;
                        break;
                    case Keyboard::Num4:
                        nextBlock = O_block();
                        exists = true;
                        break;
                    case Keyboard::Num5:
                        nextBlock = S_block();
                        exists = true;
                        break;
                    case Keyboard::Num6:
                        nextBlock = T_block();
                        exists = true;
                        break;
                    case Keyboard::Num7:
                        nextBlock = Z_block();
                        exists = true;
                        break;
                    default:
                        break;
                    }
                }
            }
            if (exists) {
                clear_sound.play();
                break;
            }
            clock_t end = clock();
        } while ((end - start) / CLOCKS_PER_SEC <= 5);
    }
    else {
        denied_sound.play();
    }

}