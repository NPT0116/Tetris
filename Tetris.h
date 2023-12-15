#pragma once
#include "Block_Type.cpp"
#include "Position.h"
#include "SFML/Audio/Sound.hpp"
#include <vector>
#include <time.h>
#include <SFML/Audio.hpp>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <future>
#include <thread>
#include <queue>
using namespace std;
using namespace sf;
class Tetris
{
private:
    Block currBlock;
    Block nextBlock;
    Block ghost_Block;
    vector <int> skill_list;
public:
    // Thời gian block move down
    sf::Clock clock_event;
    float elapsedTime;
    float interval;


    GameBox box;
    bool drop_block = false;
    bool gameOver = false;
    vector <Block>blocks;
    vector <Block>get_all_type_block();
    Tetris();

    //trả về địa chỉ của 1 block.
    Block randomBlock();
    void hand_input(Event& event, RenderWindow& window);
    void moveBlockLeft();
    void moveBlockRight();
    void moveBlockDown(RenderWindow& window);
    void Draw(RenderWindow& window);
    void moveBlockSpace();
    bool is_block_outside(bool check_ghost = false);
    void rotate_block(bool check_ghost_block = false);
    void lock_block(RenderWindow& window);
    bool is_block_fit(bool check_ghost = false);
    void check_completed_row();
    void game_over();
    void restart_game();
    void draw_next_block(RenderWindow& window);
    void lock_ghost_block();
    void Drop_ghost_block();
    void Update_ghost_block();
    // Điểm số 
    int score;
    void UpdateScore(int LinesCleared, int moveDownPoint);
    // Âm thanh
    Music game_sound;
    Music flip_sound;
    Music clear_sound;
    Music drop_sound;
    Music end_sound;
    Music denied_sound;
    Music disapear_sound;
    // Thời gian game chạy 
    clock_t begin, end;
    // Tốc độ rơi
    double speed;
    // Skill
    int Next_skill;
    void Random_Next_skill();
    void Boom_block(RenderWindow& window);
    void Clear_row(RenderWindow& window);
    void Pick_Block(RenderWindow& window);
    void Slow_speed(RenderWindow& windows);
    int count_score;
    void Draw_next_skill(RenderWindow& window);
    void Count_skill(int& bb, int& cr, int& pb, int& sp);
    void Draw_count_skill(RenderWindow& window);
    bool skill_list_check(int n);
    int wait_for_fill;
    bool temp_int;
    ~Tetris();
};

