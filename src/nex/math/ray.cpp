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

} //namespace nx
