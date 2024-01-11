#include "Tetris.hpp"

Tetris::Tetris(TetrisData *TetrisData) : m_direction(UP), m_offset({3, -4})
{
    m_shape = rand() % 7;
    m_color = rand() % 4 + 10;
    m_vec = TetrisData->getVec(m_shape, m_direction);
}

const Vec2 Tetris::getVec2(const Vec2 &it) const
{
    return it + m_offset;
}

const Vec2 Tetris::getVec2(int idx) const
{
    return m_vec[idx] + m_offset;
}

int Tetris::getColor() const
{
    return m_color;
}

bool Tetris::overEdge() const
{
    for (auto const &it : m_vec)
    {
        if (getVec2(it).y <= 0)
            return true;
    }
    return false;
}

bool Tetris::hit(const std::vector<Vec2> &vec, const std::vector<std::vector<int>> &map) const
{
    for (auto const &it : vec)
    {
        if (getVec2(it).x < 0)
            return true;
        if (getVec2(it).x > 9)
            return true;
        if (getVec2(it).y < 0)
            continue;
        if (getVec2(it).y > 19)
            return true;
        if ((map[getVec2(it).x][getVec2(it).y] != 0))
            return true;
    }
    return false;
}

void Tetris::rotate(TetrisData *TetrisData, const std::vector<std::vector<int>> &map)
{
    // 旋转90度后的坐标
    std::vector<Vec2> vec = TetrisData->getVec(m_shape, (m_direction + 1) % 4);

    // 旋转后是否产生碰撞
    // 如果碰撞则不进行旋转
    if (hit(vec, map))
    {
        return;
    }
    // 如果不碰撞
    else
    {
        // 清除现有的俄罗斯方块
        clear();
        // 更新坐标、方向
        m_vec = vec;
        m_direction = (m_direction + 1) % 4;
        // 打印新的俄罗斯方块
        print();
    }
}

bool Tetris::drop(const std::vector<std::vector<int>> &map)
{
    // 下落一格
    m_offset.y++;
    // 如果碰撞则不下落
    if (hit(m_vec, map))
    {
        m_offset.y--;
        return true;
    }
    // 清除现有的俄罗斯方块
    m_offset.y--;
    clear();
    // 更新下落后的坐标
    m_offset.y++;
    // 打印新的俄罗斯方块
    print();
    return false;
}

void Tetris::left(const std::vector<std::vector<int>> &map)
{
    // 左移一格
    m_offset.x--;
    // 如果超出左边界则不左移
    if (leftEdge())
    {
        m_offset.x++;
        return;
    }
    // 如果碰撞则不左移
    if (hit(m_vec, map))
    {
        m_offset.x++;
        return;
    }
    // 清除现有的俄罗斯方块
    m_offset.x++;
    clear();
    // 打印新的俄罗斯方块
    m_offset.x--;
    print();
}
void Tetris::right(const std::vector<std::vector<int>> &map)
{
    // 右移一格
    m_offset.x++;
    // 如果超出右边界则不右移
    if (rightEdge())
    {
        m_offset.x--;
        return;
    }
    // 如果碰撞则不右移
    if (hit(m_vec, map))
    {
        m_offset.x--;
        return;
    }
    // 清除现有的俄罗斯方块
    m_offset.x--;
    clear();
    // 打印新的俄罗斯方块
    m_offset.x++;
    print();
}

void Tetris::clear()
{
    for (auto const &it : m_vec)
    {
        if (getVec2(it).y < 0)
            continue;
        else
            printClear(getVec2(it));
    }
}

void Tetris::print()
{
    for (auto const &it : m_vec)
    {
        if (getVec2(it).y < 0)
            continue;
        else
            printSquare(getVec2(it), m_color);
    }
    
    // 设置颜色
    setColor(7);
}

bool Tetris::leftEdge()
{
    for (auto const &it : m_vec)
    {
        if (getVec2(it).x < 0)
            return true;
    }
    return false;
}

bool Tetris::rightEdge()
{
    for (auto const &it : m_vec)
    {
        if (getVec2(it).x >= 10)
            return true;
    }
    return false;
}

void Tetris::operator=(const Tetris &other)
{
    m_shape = other.m_shape;
    m_direction = other.m_direction;
    m_color = other.m_color;
    m_vec = other.m_vec;
    m_offset = other.m_offset;
}