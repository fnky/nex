#include <nex/math/plane.h>
#include <cmath>

namespace nx
{

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

} //namespace nx
