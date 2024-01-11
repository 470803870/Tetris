#include "tools.hpp"

void setCursor(const Vec2 &vec)
{
    COORD pos = {(short)((vec.x + 10) * 2), (short)(vec.y + 4)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printSquare(const Vec2 &vec, int color)
{
    setCursor(vec);
    setColor(color);
    std::cout << "¡ö";
}

void printClear(const Vec2 &vec)
{
    setCursor(vec);
    std::cout << "  ";
}