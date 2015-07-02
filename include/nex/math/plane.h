#ifndef PLANE_H_INCLUDE
#define PLANE_H_INCLUDE

#include <nex/math/vec3.h>
#include <nex/math/vec4.h>

#include <nex/math/planeintersectiontype.h>

#include <nex/math/aabb.h>
#include <nex/math/sphere.h>

namespace nx
{

class Ray;

class Plane
{
public:

    /**
     * @brief  Creates a new instance of Plane.
     */
    Plane();

    /**
     * @brief Creates a new instance of Plane.
     * @param normal = The plane normal.
     * @param distance = The distance of the plane.
     */
    Plane(const vec3f& normal, const float distance);

    /**
     * @brief Creates a new instance of Plane.
     * @param vertexA = One point of a triangle defining the Plane.
     * @param vertexB = One point of a triangle defining the Plane.
     * @param vertexC = One point of a triangle defining the Plane.
     */
    Plane(const vec3f& vertexA, const vec3f& vertexB, const vec3f& vertexC);

    /**
     * @brief Changes the coefficients of the Normal vector of this Plane to make it of unit length.
     */
    void normalize();

    /**
     * @brief Calculates the dot product of a specified Vector4 and this Plane.
     * @param value = The Vector4 to multiply this Plane by.
     * @return the dot product.
     */
    float dot(const vec4f& value) const;

    /**
     * @brief Returns the dot product of a specified Vector3 and the Normal vector of this Plane plus the distance (D) value of the Plane.
     * @param The Vector3 to multiply by.
     * @return the dot coordinate.
     */
    float dotCoordinate(const vec3f& value) const;

    /**
     * @brief Returns the dot product of a specified Vector3 and the Normal vector of this Plane.
     * @param value = The Vector3 to multiply by.
     * @return the dot normal.
     */
    float dotNormal(const vec3f& value) const;

    /**
     * @brief Checks whether the current Plane intersects a specified BoundingBox.
     * @param box = The BoundingBox to test for intersection with.
     * @return the intersection results.
     */
    PlaneIntersectionType intersects(const AABB& box) const;

    /**
     * @brief Checks whether the current Plane intersects a specified BoundingSphere.
     * @param sphere = The BoundingSphere to check for intersection with.
     * @return the intersection results.
     */
    PlaneIntersectionType intersects(const Sphere& sphere) const;

    /**
     * @brief Changes the coefficients of the Normal vector of this Plane to make it of unit length.
     * @param plane = plane to  normalize.
     * @return the normalized plane.
     */
    static Plane normalize(const Plane& plane);

    /**
     * @brief Compute the resulting line intersection between two planes if any.
     * @param p1 = The first plane.
     * @param p2 = The second plane.
     * @return the intersection.
     */
    static Ray computeIntersectionLine(const Plane& p1, const Plane& p2);

    /**
     * @brief The normal vector of the Plane.
     */
    vec3f normal;

    /**
     * @brief The distance of the Plane along its normal from the origin.
     */
    float distance;
}; //class Plane

#include <nex/math/plane.inl>

} //namespace nx

#endif // PLANE_H_INCLUDE
