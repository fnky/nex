#include <nex/math/boundingsphere.h>
#include <nex/math/boundingbox.h>

namespace nx
{

BoundingSphere::BoundingSphere() :
    center(vec3f()),
    radius(0.0f)
{ }

BoundingSphere::BoundingSphere(const vec3f center, const float radius) :
    center(center),
    radius(radius)
{ }

inline BoundingSphere BoundingSphere::createMerged(const BoundingSphere& original, const BoundingSphere& additional)
{
    const vec3f result = additional.center - original.center;
    const float resultLength = result.length();
    const float radiusA = original.radius;
    const float radiusB = additional.radius;

    if (radiusA + radiusB >= resultLength)
    {
        if (radiusA - radiusB >= resultLength)
            return original;
        if (radiusB - radiusA >= resultLength)
            return additional;
    }

    const vec3f oneOverLength = result * (1.0f / resultLength);

    const float minRad = min(-radiusA, resultLength - radiusB);
    const float maxRad = ((max(radiusA, resultLength + radiusB) - minRad) * 0.5f);

    BoundingSphere resultSphere;

    resultSphere.center = original.center + oneOverLength * (maxRad + minRad);
    resultSphere.radius = maxRad;

    return resultSphere;
}

inline BoundingSphere BoundingSphere::createFromBoundingBox(const BoundingBox& box)
{
    BoundingSphere boundingSphere;
    boundingSphere.center = vec3f::lerp(box.min, box.max, 0.5f);

    const float resultRadius = vec3f::distance(box.max, box.max);
    boundingSphere.radius = resultRadius * 0.5f;
    return boundingSphere;
}

} //namespace nx
