#pragma once
#include <thread>
#include <chrono>
#include <ctime>
#include "conio.h"
#include "Tetris.hpp"

class Game
{
private:
    std::vector<std::vector<int>> m_map;
    TetrisData *m_data;
    Tetris *m_cur, *m_next;
    bool m_GameOver;
    
    Game();
    void GameStart();
    void printMap() const;
    void printNext() const;
    void keyBoardMove();
    void drop();
    void lineClear();

public:
    static Game &getInstance(); 
};