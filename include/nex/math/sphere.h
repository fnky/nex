#ifndef BOUNDINGSPHERE_H_INCLUDE
#define BOUNDINGSPHERE_H_INCLUDE

#include <vector>

#include <nex/math/mathhelper.h>

#include <nex/math/vec3.h>

#include <nex/math/aabb.h>

namespace nx
{
class AABB;
class Frustum;

/**
 * @brief Defines a sphere.
 */
class Sphere
{
public:

    /**
     * @brief Creates a new instance of BoundingSphere.
     */
    Sphere();

    /**
     * @brief Creates a new instance of BoundingSphere.
     * @param center = Center point of the sphere.
     * @param radius = Radius of the sphere.
     */
    Sphere(const vec3f center, const float radius);

    /**
     * @brief Checks whether the current BoundingSphere intersects with a specified BoundingSphere.
     * @param sphere = The BoundingSphere to check for intersection with the current BoundingSphere.
     * @return the intersection result.
     */
    bool intersects(const Sphere& sphere) const;

    /**
     * @brief Checks whether the current BoundingSphere intersects with a specified BoundingBox.
     * @param box = The BoundingBox to check for intersection with the current BoundingSphere.
     * @return the intersection results.
     */
    bool intersects(const AABB& box) const;

    /**
     * @brief Checks whether the current BoundingSphere contains the specified BoundingBox.
     * @param box = The BoundingBox to check against the current BoundingSphere.
     * @return the containment type.
     */
    ContainmentType contains(const AABB& box) const;

    /**
     * @brief Checks whether the current BoundingSphere contains the specified BoundingFrustum.
     * @param frustum = The BoundingFrustum to check against the current BoundingSphere.
     * @return the containment type.
     */
    ContainmentType contains(const Frustum& frustum) const;

    /**
     * @brief Checks whether the current BoundingSphere contains the specified point.
     * @param point = The point to check against the current BoundingSphere.
     * @return the containment type.
     */
    ContainmentType contains(const vec3f& point) const;

    /**
     * @brief Checks whether the current BoundingSphere contains the specified BoundingSphere.
     * @param sphere = The BoundingSphere to check against the current BoundingSphere.
     * @return the containment type.
     */
    ContainmentType contains(const Sphere& sphere) const;

    /**
     * @brief Creates a BoundingSphere that contains the two specified BoundingSphere instances.
     * @param original = BoundingSphere to be merged.
     * @param additional = BoundingSphere to be merged.
     * @return the resulting sphere.
     */
    static Sphere createMerged(const Sphere& original, const Sphere& additional);

    /**
     * @brief Creates the smallest BoundingSphere that can contain a specified BoundingBox.
     * @param The BoundingBox to create the BoundingSphere from.
     * @return the resulting sphere.
     */
    static Sphere createFromBoundingBox(const AABB& box);

    /**
     * @brief Creates a BoundingSphere that can contain a specified list of points.
     * @param points = List of points the BoundingSphere must contain.
     * @return the resulting sphere.
     */
    static Sphere createFromPoints(std::vector<vec3f> points);

    /**
     * @brief The center point of the sphere.
     */
    vec3f center;

    /**
     * @brief The radius of the sphere.
     */
    float radius;

}; //namespace BoundingSphere
} //namespace nx

#endif // BOUNDINGSPHERE_H_INCLUDE
