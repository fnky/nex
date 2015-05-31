#include <nex/math/ray.h>
#include <nex/math/mathhelper.h>

#include <cmath>
#include <limits>

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

float Ray::intersects(const BoundingBox& boundingBox) const
{
    float result = 0.0f;
    float clip = std::numeric_limits<float>::max();

    if (fabs(direction.x) < 9.99999997475243E-07f)
    {
        if (position.x < boundingBox.min.x || position.x > boundingBox.max.x)
            return 0.0f;
    }
    else
    {
        float oneOverX = 1.0f / direction.x;
        float minX = (boundingBox.min.x - position.x) * oneOverX;
        float maxX = (boundingBox.max.x - position.x) * oneOverX;

        if (minX > maxX)
        {
            float swap = minX;
            minX = maxX;
            maxX = swap;
        }

        result = max(minX, result);
        clip = min(maxX, clip);

        if (result > clip)
           return 0.0f;
    }

    if (fabs(direction.y) < 9.99999997475243E-07f)
    {
        if (position.y < boundingBox.min.y || position.y > boundingBox.max.y)
            return 0.0f;
    }
    else
    {
        float oneOverY = 1.0f / direction.y;
        float minY = (boundingBox.min.y - position.y) * oneOverY;
        float maxY = (boundingBox.max.y - position.y) * oneOverY;

        if (minY > maxY)
        {
            float swap = minY;
            minY = maxY;
            maxY = swap;
        }

        result = max(minY, result);
        clip = min(maxY, clip);

        if (result > clip)
            return 0.0f;
    }

    if (fabs(direction.z) < 9.99999997475243E-07f)
    {
        if (position.z < boundingBox.min.z || position.z > boundingBox.max.z)
            return 0.0f;
    }
    else
    {
        float oneOverZ = 1.0f / direction.z;

        float minZ = (boundingBox.min.z - position.z) * oneOverZ;
        float maxZ = (boundingBox.max.z - position.z) * oneOverZ;

        if (minZ > maxZ)
        {
            float swap = minZ;
            minZ = maxZ;
            maxZ = swap;
        }

        result = max(minZ, result);
        float minClip = min(maxZ, clip);

        if (result > minClip)
            return 0.0f;
    }
    return result;
}

inline vec3f Ray::computeIntersection(const Plane& plane) const
{
    const float distance = (-plane.distance - vec3f::dot(plane.normal, position)) / vec3f::dot(plane.normal, direction);
    return (position + direction) * distance;
}

} //namespace nx
