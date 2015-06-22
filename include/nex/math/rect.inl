template <typename T>
Rect<T>::Rect() :
    x(0),
    y(0),
    width(0),
    height(0)
{ }

template <typename T>
Rect<T>::Rect(T x, T y, T width, T height) :
    x(x),
    y(y),
    width(width),
    height(height)
{ }

template <typename T>
template <typename U>
Rect<T>::Rect(const Rect<U>& rectangle) :
    x(static_cast<T>(rectangle.x)),
    y(static_cast<T>(rectangle.y)),
    width(static_cast<T>(rectangle.width)),
    height(static_cast<T>(rectangle.height))
{ }

template <typename T>
bool Rect<T>::contains(T x, T y) const
{
    // Rectangles with negative dimensions are allowed, so we must handle them correctly

    // Compute the real min and max of the rectangle on both axes
    T minX = std::min(x, static_cast<T>(x + width));
    T maxX = std::max(x, static_cast<T>(x + width));
    T minY = std::min(y, static_cast<T>(y + height));
    T maxY = std::max(y, static_cast<T>(y + height));

    return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
}

template <typename T>
bool Rect<T>::contains(const Vec2<T>& point) const
{
    return contains(point.x, point.y);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& rectangle) const
{
    Rect<T> intersection;
    return intersects(rectangle, intersection);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& rectangle, Rect<T>& intersection) const
{
    // Rectangles with negative dimensions are allowed, so we must handle them correctly

    // Compute the min and max of the first rectangle on both axes
    T r1MinX = std::min(x, static_cast<T>(x + width));
    T r1MaxX = std::max(x, static_cast<T>(x + width));
    T r1MinY = std::min(y, static_cast<T>(y + height));
    T r1MaxY = std::max(y, static_cast<T>(y + height));

    // Compute the min and max of the second rectangle on both axes
    T r2MinX = std::min(rectangle.x, static_cast<T>(rectangle.x + rectangle.width));
    T r2MaxX = std::max(rectangle.x, static_cast<T>(rectangle.x + rectangle.width));
    T r2MinY = std::min(rectangle.y, static_cast<T>(rectangle.y + rectangle.height));
    T r2MaxY = std::max(rectangle.y, static_cast<T>(rectangle.y + rectangle.height));

    // Compute the intersection boundaries
    T interLeft   = std::max(r1MinX, r2MinX);
    T interTop    = std::max(r1MinY, r2MinY);
    T interRight  = std::min(r1MaxX, r2MaxX);
    T interBottom = std::min(r1MaxY, r2MaxY);

    // If the intersection is valid (positive non zero area), then there is an intersection
    if ((interLeft < interRight) && (interTop < interBottom))
    {
        intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
        return true;
    }
    else
    {
        intersection = Rect<T>(0, 0, 0, 0);
        return false;
    }
}


////////////////////////////////////////////////////////////
template <typename T>
inline bool operator ==(const Rect<T>& left, const Rect<T>& right)
{
    return (left.x == right.x) && (left.width == right.width) &&
           (left.y == right.y) && (left.height == right.height);
}


////////////////////////////////////////////////////////////
template <typename T>
inline bool operator !=(const Rect<T>& left, const Rect<T>& right)
{
    return !(left == right);
}
