#include "Game.hpp"

Game::Game() : m_GameOver(false)
{
    // 随机数种子
    srand(unsigned(time(NULL)));
    // 地图初始化10*20
    m_map.resize(10);
    for (size_t i = 0; i < 10; i++)
        m_map[i].resize(20);
    // 俄罗斯方块坐标数据初始化
    m_data = &TetrisData::getInstance();
    // 初始化当前俄罗斯方块
    m_cur = new Tetris(m_data);
    // 初始化下一个俄罗斯方块
    m_next = new Tetris(m_data);
    // 绘制地图
    printMap();
    // 开始游戏
    GameStart();
    // 释放内存
    delete m_cur, m_next;
}

Game &Game::getInstance()
{
    // 单例模式（静态实例，构造函数私有）
    static Game m_instance;
    // 返回实例
    return m_instance;
}

void Game::GameStart()
{
    // 游戏循环
    while (true)
    {
        // 每隔200毫秒下落一格
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        // 根据键盘WASD移动
        keyBoardMove();
        // 下落（碰撞、消行、游戏结束）
        drop();
        // 游戏结束
        if (m_GameOver)
            break;
    }
}

void Game::printMap() const
{
    // 上边框
    for (int i = -1; i < 16; i++)
        printSquare({i, -1}, 1);
    // 每一行打印
    for (int y = 0; y < 20; y++)
    {
        // 最左侧方框
        printSquare({-1, y}, 1);
        // 10列游戏界面
        for (int x = 0; x < 10; x++)
            printClear({x, y});
        // 游戏界面右侧方框
        printSquare({10, y}, 1);
        // 显示下一个俄罗斯方块的4格
        for (int i = 0; i < 4; i++)
            printClear({i + 11, y});
        // 最右侧方框
        printSquare({15, y}, 1);
    }
    // 右侧分割线
    for (int i = 11; i < 15; i++)
        printSquare({i, 15}, 1);

    // 下边框
    for (int i = -1; i < 16; i++)
        printSquare({i, 20}, 1);

    // 打印下一个俄罗斯方块
    printNext();

    // 设置颜色
    setColor(7);

    // 设置光标
    setCursor({30, 25});
}

void Game::keyBoardMove()
{
    int key = 0;
    while (_kbhit())
    {
        key = _getch();
        switch (key)
        {
        case 119: // W
            m_cur->rotate(m_data, m_map);
            break;
        case 115: // S
            break;
        case 97: // A
            m_cur->left(m_map);
            break;
        case 100: // D
            m_cur->right(m_map);
            break;

        default:
            break;
        }
        setCursor({30, 25});
    }
}

void Game::drop()
{
    // 如果下落产生碰撞
    if (m_cur->drop(m_map) == true)
    {
        // 如果达到上边界，游戏结束
        if (m_cur->overEdge() == true)
        {
            m_GameOver = true;
            return;
        }

        // 消除行
        lineClear();

        // 获取新的俄罗斯方块
        // 当前俄罗斯方块换成下一个俄罗斯方块
        *m_cur = *m_next;
        // 下一格俄罗斯方块随机生成
        *m_next = Tetris(m_data);
        // 打印下一个俄罗斯方块
        printNext();
    }
    setCursor({30, 25});
}

void Game::printNext() const
{
    // 清空
    for (int x = 11; x < 15; x++)
    {
        for (int y = 16; y < 20; y++)
        {
            printClear({x, y});
        }
    }

    // 打印下一个俄罗斯方块
    for (int i = 0; i < 4; i++)
    {
        Vec2 vec = m_next->getVec2(i);
        printSquare({vec.x + 8, vec.y + 20}, m_next->getColor());
    }
    
    // 设置颜色
    setColor(7);
}

void Game::lineClear()
{
    // 计算那些行可以消
    std::vector<int> lines;
    // 标记是否可以消
    bool flag = true;

    // 地图中记录当前俄罗斯方块
    for (int i = 0; i < 4; i++)
    {
        Vec2 vec = m_cur->getVec2(i);
        m_map[vec.x][vec.y] = m_cur->getColor();
    }

    // 从右往左遍历（删除元素时，左侧的行号不会变）
    for (size_t y = 19; y > 0; y--) // 0行游戏结束，排除在外
    {
        // 设置标记为true
        flag = true;
        // 判断这一行是否都有俄罗斯方块
        for (size_t x = 0; x < 10; x++)
        {
            // 如果有空则跳出循环
            if (m_map[x][y] == 0)
            {
                flag = false;
                break;
            }
        }
        // 如果这一行可以消，记录行号
        if (flag)
        {
            lines.push_back(y);
        }
    }

    // 如果有行可以消
    if (lines.size() != 0)
    {
        // 从右往左每一列删除该行元素

        // 从右往左遍历行数（删除元素时，左侧的行号不会变）
        for (auto it : lines)
        {
            // 每一列删除该行元素
            for (size_t i = 0; i < 10; i++)
            {
                // 删除该行元素
                // 防止迭代器越界
                if (it >= 19)
                {
                    m_map[i].erase(m_map[i].begin() + 19);
                }
                else
                {
                    m_map[i].erase(m_map[i].begin() + it, m_map[i].begin() + it + 1);
                }
            }
        }

        // 在数组头加入删除的N个元素
        // 删除N行重复N次
        for (auto it : lines)
        {
            // 每一列在数组头加入0（空元素）
            for (size_t i = 0; i < 10; i++)
            {
                m_map[i].insert(m_map[i].begin(), 0);
            }
        }

        // 根据消行后的地图重新打印
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                printSquare({i, j}, m_map[i][j]);
            }
        }
    }
    
    // 设置颜色
    setColor(7);
}