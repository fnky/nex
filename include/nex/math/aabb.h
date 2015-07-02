#ifndef BOUNDINGBOX_H_INCLUDE
#define BOUNDINGBOX_H_INCLUDE

#include <vector>

#include <nex/math/vec3.h>

#include <nex/math/containmenttype.h>

namespace nx
{
class Sphere;

/**
 * @brief Defines an axis-aligned box-shaped 3D volume.
 */
class AABB
{
public:

    /**
     * @brief Creates an instance of BoundingBox.
     */
    AABB();

    /**
     * @brief Creates an instance of BoundingBox.
     * @param min = The minimum point the BoundingBox includes.
     * @param max = The maximum point the BoundingBox includes.
     */
    AABB(const vec3f min, const vec3f max);

    /**
     * @brief Specifies the total number of corners (8) in the BoundingBox.
     */
    const int32 CornerCount = 8;

    /**
     * @brief Gets an array of points that make up the corners of the BoundingBox.
     * @return points.
     */
    std::vector<vec3f> getCorners();

    /**
     * @brief Checks whether the current BoundingBox intersects another BoundingBox.
     * @param box = The BoundingBox to check for intersection with.
     * @return the intersection result.
     */
    bool intersects(const AABB& box) const;

    /**
     * @brief Checks whether the current BoundingBox intersects a BoundingSphere.
     * @param sphere = The BoundingSphere to check for intersection with.
     * @return the intersection result.
     */
    bool intersects(const Sphere& sphere) const;

    /**
     * @brief Tests whether the BoundingBox contains another BoundingBox.
     * @param box = The BoundingBox to test for overlap.
     * @return The ContainmentType.
     */
    ContainmentType contains(const AABB& box) const;

    /**
     * @brief Tests whether the BoundingBox contains a point.
     * @param point = The point to test for overlap.
     * @return The ContainmentType.
     */
    ContainmentType contains(const vec3f& point) const;

    /**
     * @brief Creates the smallest BoundingBox that contains the two specified BoundingBox instances.
     * @param original = One of the BoundingBoxs to contain.
     * @param additional = One of the BoundingBoxs to contain.
     * @return smallest BoundingBox that contains the two.
     */
    static AABB createMerged(const AABB& original, const AABB& additional);

    /**
     * @brief Creates the smallest BoundingBox that will contain the specified BoundingSphere.
     * @param sphere = The BoundingSphere to contain.
     * @return the bounding box containg the sphere.
     */
    static AABB createFromSphere(const Sphere& sphere);

    /**
     * @brief Creates the smallest BoundingBox that will contain a group of points.
     * @param points = A list of points the BoundingBox should contain.
     * @return the bounding box containing the points.
     */
    static AABB createFromPoints(const std::vector<vec3f> points);

    /**
     * @brief The minimum point the BoundingBox contains.
     */
    vec3f min;

    /**
     * @brief The maximum point the BoundingBox contains.
     */
    vec3f max;
}; //class BoundingBox
} //namespace nx

#endif // BOUNDINGBOX_H_INCLUDE
