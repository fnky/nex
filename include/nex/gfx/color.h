#ifndef COLOR_H_INCLUDE
#define COLOR_H_INCLUDE

#include <nex/system/typedefs.h>
#include <nex/math/vec3.h>

namespace nx
{

class Color
{
public:

    /**
     * @brief Construct a default color (0, 0, 0, 255)
     */
    Color();

    /**
     * @brief Construct a color with the specified values.
     * @param red = The red component (0-255)
     * @param green = The green component (0-255)
     * @param blue = The blue component (0-255)
     * @param alpha = The alpha component (0-255)
     */
    Color(uint8 red, uint8 green, uint8 blue, uint8 alpha = 255);

    /**
     * @brief Construct the color from 32-bit unsigned integer
     * @param color = Number containing the RGBA components (in that order)
     */
    explicit Color(uint32 color);

    /**
     * @brief Retrieve the color as a 32-bit unsigned integer
     * @return Color represented as a 32-bit unsigned integer
     */
    uint32 toInteger() const;

    /**
     * @brief Retrive the color as a floating point vector (0.0 <-> 1.0)
     * @return vec3f as a color.
     */
    vec3f toVector() const;

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color Transparent;

    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
};

bool operator ==(const Color& left, const Color& right);

bool operator !=(const Color& left, const Color& right);

Color operator +(const Color& left, const Color& right);

Color operator -(const Color& left, const Color& right);

Color operator *(const Color& left, const Color& right);

Color& operator +=(Color& left, const Color& right);

Color& operator -=(Color& left, const Color& right);

Color& operator *=(Color& left, const Color& right);

} // namespace nx

#endif // COLOR_H_INCLUDE
