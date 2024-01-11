#pragma once
#include <vector>
#include "stdlib.h"
#include "tools.hpp"
#include "Vec2.hpp"
#include "TetrisData.hpp" 

class Tetris
{
private:
    int m_shape;
    int m_direction;
    int m_color;
    std::vector<Vec2> m_vec;
    Vec2 m_offset;

    void clear();
    void print();
    bool leftEdge();
    bool rightEdge();

public:
    Tetris(TetrisData *TetrisData);
    void rotate(TetrisData *TetrisData, const std::vector<std::vector<int>> &map);
    bool drop(const std::vector<std::vector<int>> &map);
    void left(const std::vector<std::vector<int>> &map);
    void right(const std::vector<std::vector<int>> &map);
    const Vec2 getVec2(const Vec2 &it) const;
    const Vec2 getVec2(int idx) const;
    int getColor() const;
    bool overEdge() const;
    bool hit(const std::vector<Vec2> &vec, const std::vector<std::vector<int>> &map) const;
    void operator=(const Tetris &other);
};