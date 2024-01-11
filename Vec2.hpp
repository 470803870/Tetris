#pragma once
class Vec2
{
public:
    int x, y;

public:
    Vec2() : x(0), y(0) {}
    Vec2(int x, int y) : x(x), y(y) {}
    void operator=(const Vec2 &other);
    const Vec2 operator+(const Vec2 &other) const;
};