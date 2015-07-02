#include <nex/math/aabb.h>
#include <nex/math/sphere.h>

namespace nx
{

AABB::AABB() :
    min(vec3f()),
    max(vec3f())
{ }

AABB::AABB(const vec3f min, const vec3f max) :
    min(min),
    max(max)
{ }

std::vector<vec3f> AABB::getCorners()
{
    std::vector<vec3f> points;

    points.push_back(vec3f(min.x, max.y, max.z));
    points.push_back(vec3f(max.x, max.y, max.z));
    points.push_back(vec3f(max.x, min.y, max.z));
    points.push_back(vec3f(min.x, min.y, max.z));
    points.push_back(vec3f(min.x, max.y, min.z));
    points.push_back(vec3f(max.x, max.y, min.z));
    points.push_back(vec3f(max.x, min.y, min.z));
    points.push_back(vec3f(min.x, min.y, min.z));

    return points;
}

bool AABB::intersects(const AABB& box) const
{
    return max.x >= box.min.x &&
           min.x <= box.max.x &&
          (max.y >= box.min.y && min.y <= box.max.y) &&
          (max.z >= box.min.z && min.x <= box.max.z);
}

bool AABB::intersects(const Sphere& sphere) const
{
    const vec3f clampResult = vec3f::clamp(sphere.center, min, max);
    const float distanceSquared = vec3f::distanceSquared(sphere.center, clampResult);

    return distanceSquared <= (sphere.radius * sphere.radius);
}

ContainmentType AABB::contains(const AABB& box) const
{
    if (max.x < min.x || min.x > box.max.x || (max.y < box.min.y || min.y > box.max.y) || (max.z < box.min.z || min.z > box.max.z))
        return ContainmentType::Disjoint;

    return min.x > box.min.x ||
           box.max.x > max.x ||
          (min.y > box.min.y || box.max.y > max.y) ||
          (min.z >  box.min.z || box.max.z > max.z) ? ContainmentType::Intersects : ContainmentType::Contains;
}

ContainmentType AABB::contains(const vec3f& point) const
{
    return min.x > point.x || point.x > max.x || (min.y > point.y || point.y > max.y) || (min.z > point.z || point.z > max.z) ? ContainmentType::Disjoint : ContainmentType::Contains;
}

AABB AABB::createMerged(const AABB& original, const AABB& additional)
{
    AABB boundingBox;

    boundingBox.min = vec3f::min(original.min, additional.min);
    boundingBox.max = vec3f::max(original.max, additional.max);

    return boundingBox;
}

AABB AABB::createFromSphere(const Sphere& sphere)
{
    AABB result;

    result.min.x = sphere.center.x - sphere.radius;
    result.min.y = sphere.center.y - sphere.radius;
    result.min.z = sphere.center.z - sphere.radius;
    result.max.x = sphere.center.x + sphere.radius;
    result.max.y = sphere.center.y + sphere.radius;
    result.max.z = sphere.center.z + sphere.radius;

    return result;
}

AABB AABB::createFromPoints(const std::vector<vec3f> points)
{
    vec3f min;
    vec3f max;

    for (auto& point : points)
    {
        min = vec3f::min(min, point);
        max = vec3f::max(max, point);
    }

    return AABB(min, max);
}

} //namespace nx
