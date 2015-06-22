#ifndef RECT_H_INCLUDE
#define RECT_H_INCLUDE

// Nex includes.
#include <nex/math/vec2.h>

// Standard includes.
#include <algorithm>

namespace nx
{

template <typename T>
class Rect
{
public:

    /**
     * @brief Default constructor (zeros out all values)
     */
    Rect();

    /**
     * @brief Construct a rectangle.
     * @param x = The x position.
     * @param y = The y position.
     * @param width = The width.
     * @param height = The height.
     */
    Rect(T x, T y, T width, T height);

    /**
     * @brief Construct a rectangle.
     * @param position = The position of the rectangle.
     * @param size = The size of the rectangle.
     */
    Rect(const Vec2<T>& position, const Vec2<T>& size);

    /**
     * @brief Construct the rectangle from another type of rectangle.
     * @param rectangle = The rectangle of another type.
     */
    template <typename U>
    explicit Rect(const Rect<U>& rectangle);

    /**
     * @brief Check if a rectangle contains the specified point.
     * @param x = The x coordinate.
     * @param y = The y coordinate.
     * @return true if the rectangle contains the point.
     */
    bool contains(T x, T y) const;

    /**
     * @brief Check if a rectangle conatins the specified vector point.
     * @param point = The point.
     * @return true if the rectangle contains the point.
     */
    bool contains(const Vec2<T>& point) const;

    /**
     * @brief Check if the rectangle intesects a specified rectangle.
     * @param rectangle = The rectangle to check.
     * @return true if the two rectangles intersect.
     */
    bool intersects(const Rect<T>& rectangle) const;

    /**
     * @brief Check the intersection between two rectangles
     * @param rectangle = The rectangle to test against.
     * @param intersection = The output rectangle.
     * @return true if they overlap.
     */
    bool intersects(const Rect<T>& rectangle, Rect<T>& intersection) const;

    T x;
    T y;
    T width;
    T height;
};

#include "rect.inl"

typedef Rect<float> rectf;
typedef Rect<double> rectd;
typedef Rect<int32> recti;
typedef Rect<uint32> rectu;

} // namespace nx

#endif // RECT_H_INCLUDE
