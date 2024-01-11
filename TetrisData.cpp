#include "TetrisData.hpp"

TetrisData::TetrisData()
{
    m_vec.resize(7);
    for (size_t i = 0; i < 7; i++)
    {
        m_vec[i].resize(4);
        for (size_t j = 0; j < 4; j++)
        {
            m_vec[i][j].resize(4);
        }
    }

    m_vec[I][UP] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
    m_vec[I][RIGHT] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};
    m_vec[I][DOWN] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}};
    m_vec[I][LEFT] = {{0, 1}, {1, 1}, {2, 1}, {3, 1}};

    m_vec[J][UP] = {{2, 0}, {2, 1}, {1, 2}, {2, 2}};
    m_vec[J][RIGHT] = {{1, 1}, {1, 2}, {2, 2}, {3, 2}};
    m_vec[J][DOWN] = {{1, 1}, {2, 1}, {1, 2}, {1, 3}};
    m_vec[J][LEFT] = {{0, 1}, {1, 1}, {2, 1}, {2, 2}};

    m_vec[L][UP] = {{1, 0}, {1, 1}, {1, 2}, {2, 2}};
    m_vec[L][RIGHT] = {{1, 1}, {1, 2}, {2, 1}, {3, 1}};
    m_vec[L][DOWN] = {{1, 1}, {2, 1}, {2, 2}, {2, 3}};
    m_vec[L][LEFT] = {{0, 2}, {1, 2}, {2, 1}, {2, 2}};

    m_vec[O][UP] = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
    m_vec[O][RIGHT] = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
    m_vec[O][DOWN] = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
    m_vec[O][LEFT] = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};

    m_vec[S][UP] = {{0, 2}, {1, 1}, {1, 2}, {2, 1}};
    m_vec[S][RIGHT] = {{1, 1}, {1, 2}, {2, 2}, {2, 3}};
    m_vec[S][DOWN] = {{0, 2}, {1, 1}, {1, 2}, {2, 1}};
    m_vec[S][LEFT] = {{1, 1}, {1, 2}, {2, 2}, {2, 3}};

    m_vec[T][UP] = {{0, 2}, {1, 1}, {1, 2}, {2, 2}};
    m_vec[T][RIGHT] = {{1, 1}, {1, 2}, {1, 3}, {2, 2}};
    m_vec[T][DOWN] = {{0, 2}, {1, 2}, {1, 3}, {2, 2}};
    m_vec[T][LEFT] = {{0, 2}, {1, 1}, {1, 2}, {1, 3}};

    m_vec[Z][UP] = {{1, 1}, {2, 1}, {2, 2}, {3, 2}};
    m_vec[Z][RIGHT] = {{2, 2}, {2, 3}, {3, 1}, {3, 2}};
    m_vec[Z][DOWN] = {{1, 1}, {2, 1}, {2, 2}, {3, 2}};
    m_vec[Z][LEFT] = {{2, 2}, {2, 3}, {3, 1}, {3, 2}};
}

TetrisData &TetrisData::getInstance()
{
    static TetrisData m_instance;
    return m_instance;
}

const std::vector<Vec2> &TetrisData::getVec(int shape, int direction) const
{
    return m_vec[shape][direction];
}