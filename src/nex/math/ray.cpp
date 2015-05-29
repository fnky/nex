#include <nex/math/ray.h>
#include <cmath>

namespace nx
{

Ray::Ray(vec3f position, vec3f direction) :
    position(position),
    direction(direction)
{ }

float Ray::intersects(const Plane& plane) const
{
    const float dotA = (plane.normal.x * direction.x + plane.normal.y * direction.y + plane.normal.z * direction.z);

    //Check for out of bounds.
    if ((double)abs(dotA) < 9.99999974737875E-06)
        return 0.0f;

    const float dotB = (plane.normal.x * position.x + plane.normal.y * position.y + plane.normal.z * position.z);

    float distance = (-plane.distance - dotB) / dotA;

    //Check for out of bounds.
    if (distance < 0.0f)
    {
        if ((double)distance < -9.99999974737875E-06)
            return 0.0f;

        distance = 0.0f;
    }

    return distance;
}

float Ray::intersects(const BoundingSphere& sphere) const
{
    const float deltaX = sphere.center.x - position.x;
    const float deltaY = sphere.center.y - position.y;
    const float deltaZ = sphere.center.z - position.z;

    const float distance = (deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

    const float radiusSquared = sphere.radius * sphere.radius;

    if (distance <=  radiusSquared)
        return 0.0f;

    float num6 =  (deltaX * direction.x + deltaY * direction.y + deltaZ * direction.z);

    if (num6 < 0.0)
        return 0.0f;

    float num7 = distance - num6 * num6;

    if (num7 > radiusSquared)
        return 0.0f;

    float num8 = sqrtf(radiusSquared - num7);

    return (num6 - num8);
}

} //namespace nx
