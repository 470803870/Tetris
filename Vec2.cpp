#include "Vec2.hpp"

void Vec2::operator=(const Vec2 &other)
{
    x = other.x;
    y = other.y;
}

const Vec2 Vec2::operator+(const Vec2 &other) const
{
    return {x + other.x, y + other.y};
}