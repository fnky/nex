#ifndef BOUNDINGBOX_H_INCLUDE
#define BOUNDINGBOX_H_INCLUDE

#include <vector>

#include <nex/math/vec3.h>

namespace nx
{
    /**
     * @brief Defines an axis-aligned box-shaped 3D volume.
     */
    class BoundingBox
    {
    public:

        /**
         * @brief Creates an instance of BoundingBox.
         */
        BoundingBox();

        /**
         * @brief Creates an instance of BoundingBox.
         * @param min = The minimum point the BoundingBox includes.
         * @param max = The maximum point the BoundingBox includes.
         */
        BoundingBox(const vec3f min, const vec3f max);

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
         * @brief Creates the smallest BoundingBox that contains the two specified BoundingBox instances.
         * @param original = One of the BoundingBoxs to contain.
         * @param additional = One of the BoundingBoxs to contain.
         * @return smallest BoundingBox that contains the two.
         */
        static BoundingBox createMerged(const BoundingBox& original, const BoundingBox& additional);

        /**
         * @brief The minimum point the BoundingBox contains.
         */
        vec3f min;

        /**
         * @brief The maximum point the BoundingBox contains.
         */
        vec3f max;
    };
} //namespace nx

#endif // BOUNDINGBOX_H_INCLUDE
