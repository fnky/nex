#include <nex/math/plane.h>
#include <cmath>

namespace nx
{
Plane::Plane() :
    normal(vec3f()),
    distance(0.0f)
{ }
Plane::Plane(const vec3f& normal, const float distance) :
    normal(normal),
    distance(distance)
{ }

Plane::Plane(const vec3f& vertexA, const vec3f& vertexB, const vec3f& vertexC)
{
    const float deltaAX = vertexB.x - vertexA.x;
    const float deltaAY = vertexB.y - vertexA.y;
    const float deltaAZ = vertexB.z - vertexA.z;

    const float deltaBX = vertexC.x - vertexA.x;
    const float deltaBY = vertexC.y - vertexA.y;
    const float deltaBZ = vertexC.z - vertexA.z;

    const float h1 = (deltaAY * deltaBZ - deltaAZ * deltaBY);
    const float h2 = (deltaAZ * deltaBX - deltaAX * deltaBZ);
    const float h3 = (deltaAX * deltaBY - deltaAY * deltaBX);

    const float oneOverDistance = 1.0f / sqrtf(h1 * h1 + h2 * h2 + h3 * h3);

    normal.x = h1 * oneOverDistance;
    normal.y = h2 * oneOverDistance;
    normal.z = h3 * oneOverDistance;

    distance = -(normal.x * vertexA.x + normal.y * vertexA.y + normal.z * vertexA.z);
}

void Plane::normalize()
{
    const float normalLength = (normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);

    if (fabs(normalLength - 1.0f) < 1.19209289550781E-07f)
        return;

    const float oneOverLength = 1.0f / sqrtf(normalLength);

    normal.x *= oneOverLength;
    normal.y *= oneOverLength;
    normal.z *= oneOverLength;

    distance *= oneOverLength;
}

float Plane::dot(const vec4f& value) const
{
    return (normal.x * value.x + normal.y * value.y + normal.z * value.z + distance * value.w);
}

float Plane::dotCoordinate(const vec3f& value) const
{
    return (normal.x * value.x + normal.y * value.y + normal.z * value.z) + distance;
}

float Plane::dotNormal(const vec3f& value) const
{
    return (normal.x * value.x + normal.y * value.y + normal.z * value.z);
}

Plane Plane::normalize(const Plane& plane)
{
    const float normalLength = (plane.normal.x * plane.normal.x + plane.normal.y * plane. normal.y + plane.normal.z * plane.normal.z);

    if (fabs(normalLength - 1.0f) < 1.19209289550781E-07f)
        return Plane(plane.normal, plane.distance);

    const float oneOverLength = 1.0f / sqrtf(normalLength);

    Plane result;

    result.normal.x *= oneOverLength;
    result.normal.y *= oneOverLength;
    result.normal.z *= oneOverLength;

    result.distance *= oneOverLength;

    return plane;
}

} //namespace nx
