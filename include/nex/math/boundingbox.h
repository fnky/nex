#ifndef BOUNDINGBOX_H_INCLUDE
#define BOUNDINGBOX_H_INCLUDE

#include "vec3.h"

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
         * @param min = The minimum point the BoundingBox includes.
         * @param max = The maximum point the BoundingBox includes.
         */
        BoundingBox(const vec3f min, const vec3f max);

        /**
         * @brief Specifies the total number of corners (8) in the BoundingBox.
         */
        const int32 CornerCount = 8;

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
