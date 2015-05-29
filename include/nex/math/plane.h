#ifndef PLANE_H_INCLUDE
#define PLANE_H_INCLUDE

#include "vec3.h"

namespace nx
{
    class Plane
    {
    public:

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
