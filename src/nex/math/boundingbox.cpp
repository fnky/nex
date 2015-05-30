#include <nex/math/boundingbox.h>

namespace nx
{

BoundingBox::BoundingBox() :
    min(vec3f()),
    max(vec3f())
{ }

BoundingBox::BoundingBox(const vec3f min, const vec3f max) :
    min(min),
    max(max)
{ }

std::vector<vec3f> BoundingBox::getCorners()
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

BoundingBox BoundingBox::createMerged(const BoundingBox& original, const BoundingBox& additional)
{
    BoundingBox boundingBox;

    boundingBox.min = vec3f::min(original.min, additional.min);
    boundingBox.max = vec3f::max(original.max, additional.max);

    return boundingBox;
}

BoundingBox BoundingBox::createFromSphere(const BoundingSphere& sphere)
{
    BoundingBox result;

    result.min.x = sphere.center.x - sphere.radius;
    result.min.y = sphere.center.y - sphere.radius;
    result.min.z = sphere.center.z - sphere.radius;
    result.max.x = sphere.center.x + sphere.radius;
    result.max.y = sphere.center.y + sphere.radius;
    result.max.z = sphere.center.z + sphere.radius;

    return result;
}

} //namespace nx
