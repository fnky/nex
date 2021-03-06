#ifndef RAY_H_INCLUDE
#define RAY_H_INCLUDE

#include <nex/math/vec3.h>
#include <nex/math/plane.h>

#include <nex/math/aabb.h>
#include <nex/math/sphere.h>
#include <nex/math/frustum.h>

namespace nx
{
/*
 * TODO:
 * float intersects(BoundingFrustum frustum)
 **/
class Ray
{
public:

    /**
     * @brief Constructs a ray.
     */
    Ray();

    /**
     * @brief Constructs a ray.
     * @param position = postition of the ray.
     * @param direction = unit vector direction.
     */
    Ray(vec3f position, vec3f direction);

    /**
     * @brief Determines whether this Ray intersects a specified Plane.
     * @param The Plane with which to calculate this Ray's intersection.
     * @return intersection result.
     */
    float intersects(const Plane& plane) const;

    /**
     * @brief Checks whether the Ray intersects a specified BoundingSphere
     * @param sphere = The BoundingSphere to check for intersection with the Ray.
     * @return intersection result.
     */
    float intersects(const Sphere& sphere) const;

    /**
     * @brief Checks whether the Ray intersects a specified BoundingBox
     * @param boundingBox = The BoundingBox to check for intersection with the Ray.
     * @return intersection result.
     */
    float intersects(const AABB& boundingBox) const;

    /**
     * @brief Computes the intersections between the ray an plane.
     * @param plane = plane to compute the intersection on.
     * @return the intersection point.
     */
    vec3f computeIntersection(const Plane& plane) const;

    /**
     * @brief Specifies the starting point of the Ray.
     */
    vec3f position;

    /**
     * @brief Unit vector specifying the direction the Ray is pointing.
     */
    vec3f direction;
}; //class Ray

#include <nex/math/ray.inl>

} //namespace nx

#endif // RAY_H_INCLUDE
