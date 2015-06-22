#include <nex/gfx/color.h>

#include <algorithm>

namespace nx
{

const Color Color::Black(0, 0, 0);
const Color Color::White(255, 255, 255);
const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Yellow(255, 255, 0);
const Color Color::Magenta(255, 0, 255);
const Color Color::Cyan(0, 255, 255);
const Color Color::Transparent(0, 0, 0, 0);

Color::Color() :
    r(0),
    g(0),
    b(0),
    a(255)
{ }

Color::Color(uint8 red, uint8 green, uint8 blue, uint8 alpha) :
    r(red),
    g(green),
    b(blue),
    a(alpha)
{ }

Color::Color(uint32 color) :
    r((color & 0xff000000) >> 24),
    g((color & 0x00ff0000) >> 16),
    b((color & 0x0000ff00) >> 8 ),
    a((color & 0x000000ff) >> 0 )
{ }

uint32 Color::toInteger() const
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

bool operator ==(const Color& left, const Color& right)
{
    return (left.r == right.r) &&
           (left.g == right.g) &&
           (left.b == right.b) &&
           (left.a == right.a);
}

bool operator !=(const Color& left, const Color& right)
{
    return !(left == right);
}

Color operator +(const Color& left, const Color& right)
{
    return Color(uint8(std::min(int(left.r) + right.r, 255)),
                 uint8(std::min(int(left.g) + right.g, 255)),
                 uint8(std::min(int(left.b) + right.b, 255)),
                 uint8(std::min(int(left.a) + right.a, 255)));
}

Color operator -(const Color& left, const Color& right)
{
    return Color(uint8(std::max(int(left.r) - right.r, 0)),
                 uint8(std::max(int(left.g) - right.g, 0)),
                 uint8(std::max(int(left.b) - right.b, 0)),
                 uint8(std::max(int(left.a) - right.a, 0)));
}

Color operator *(const Color& left, const Color& right)
{
    return Color(uint8(int(left.r) * right.r / 255),
                 uint8(int(left.g) * right.g / 255),
                 uint8(int(left.b) * right.b / 255),
                 uint8(int(left.a) * right.a / 255));
}

Color& operator +=(Color& left, const Color& right)
{
    return left = left + right;
}

Color& operator -=(Color& left, const Color& right)
{
    return left = left - right;
}

Color& operator *=(Color& left, const Color& right)
{
    return left = left * right;
}

} // namespace nx
