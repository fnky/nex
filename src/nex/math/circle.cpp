#include <nex/math/circle.h>
#include <nex/math/mathhelper.h>

namespace nx
{

Circle::Circle() :
    radius(0.0f),
    center(vec2f())
{ }

Circle::Circle(vec2f center, real32 radius) :
    radius(radius),
    center(center)
{ }

bool Circle::intersects(const Circle& circle, const rectf& rect)
{
    return intersects(circle.center, circle.radius, rect);
}

bool Circle::intersects(const vec2f& center, const real32 radius, const rectf& rect)
{
    // clamp(value, min, max) - limits value to the range min..max

    // Find the closest point to the circle within the rectangle
    const real32 closestX = clamp(center.x, rect.x, rect.x + rect.width);
    const real32 closestY = clamp(center.y, rect.y, rect.y + rect.height);

    // Calculate the distance between the circle's center and this closest point
    const real32 distanceX = center.x - closestX;
    const real32 distanceY = center.y - closestY;

    // If the distance is less than the circle's radius, an intersection occurs
    const real32 distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    return distanceSquared < (radius * radius);
}

} // namespace nx
