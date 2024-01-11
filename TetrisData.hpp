#pragma once
#include <vector>
#include "Vec2.hpp"
#include "enums.hpp"

struct TetrisData
{
private:
    std::vector<std::vector<std::vector<Vec2>>> m_vec;
    TetrisData();

public:
    static TetrisData &getInstance();
    const std::vector<Vec2> &getVec(int shape, int direction) const;
};