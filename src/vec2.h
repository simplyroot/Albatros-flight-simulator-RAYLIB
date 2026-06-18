//g++ -Wall -Wextra src/vec2_test.cpp -o vec2_test.exe && ./vec2.exe
#pragma once
#include <cmath>

struct Vec2{
    float x,y;
    Vec2 operator+(const Vec2& o) const { return Vec2{ x + o.x, y + o.y }; }
    Vec2 operator-(const Vec2& o) const { return Vec2{ x - o.x, y - o.y }; }
    Vec2 operator*(float s) const { return Vec2{ x * s, y * s }; }
    float length() const { return std::sqrt(x * x + y * y); }
};