#ifndef PLANE_H_INCLUDE
#define PLANE_H_INCLUDE

#include "vec3.h"

namespace nx
{
    class Plane
    {
    public:
        Plane(vec3f normal, float distance);

        /**
         * @brief The normal vector of the Plane.
         */
        vec3f normal;

        /**
         * @brief The distance of the Plane along its normal from the origin.
         */
        float distance;
    };

#include <nex/math/plane.inl>

}

#endif // PLANE_H_INCLUDE
