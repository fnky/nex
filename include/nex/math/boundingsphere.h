#ifndef BOUNDINGSPHERE_H_INCLUDE
#define BOUNDINGSPHERE_H_INCLUDE

#include <vector>

#include <nex/math/mathhelper.h>

#include <nex/math/vec3.h>

#include <nex/math/boundingbox.h>

namespace nx
{
    class BoundingBox;

    /**
     * @brief Defines a sphere.
     */
    class BoundingSphere
    {
    public:

        /**
         * @brief Creates a new instance of BoundingSphere.
         */
        BoundingSphere();

        /**
         * @brief Creates a new instance of BoundingSphere.
         * @param center = Center point of the sphere.
         * @param radius = Radius of the sphere.
         */
        BoundingSphere(const vec3f center, const float radius);

        /**
         * @brief Checks whether the current BoundingSphere intersects with a specified BoundingSphere.
         * @param sphere = The BoundingSphere to check for intersection with the current BoundingSphere.
         * @return the intersection result.
         */
        bool intersects(const BoundingSphere& sphere) const;

        /**
         * @brief Checks whether the current BoundingSphere intersects with a specified BoundingBox.
         * @param box = The BoundingBox to check for intersection with the current BoundingSphere.
         * @return the intersection results.
         */
        bool intersects(const BoundingBox& box) const;

        /**
         * @brief Creates a BoundingSphere that contains the two specified BoundingSphere instances.
         * @param original = BoundingSphere to be merged.
         * @param additional = BoundingSphere to be merged.
         * @return the resulting sphere.
         */
        static BoundingSphere createMerged(const BoundingSphere& original, const BoundingSphere& additional);

        /**
         * @brief Creates the smallest BoundingSphere that can contain a specified BoundingBox.
         * @param The BoundingBox to create the BoundingSphere from.
         * @return the resulting sphere.
         */
        static BoundingSphere createFromBoundingBox(const BoundingBox& box);

        /**
         * @brief Creates a BoundingSphere that can contain a specified list of points.
         * @param points = List of points the BoundingSphere must contain.
         * @return the resulting sphere.
         */
        static BoundingSphere createFromPoints(std::vector<vec3f> points);

        /**
         * @brief The center point of the sphere.
         */
        vec3f center;

        /**
         * @brief The radius of the sphere.
         */
        float radius;

    };
} //namespace nx

#endif // BOUNDINGSPHERE_H_INCLUDE
