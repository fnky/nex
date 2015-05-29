#ifndef BOUNDINGSPHERE_H_INCLUDE
#define BOUNDINGSPHERE_H_INCLUDE

#include <nex/math/vec3.h>

namespace nx
{
    /**
     * @brief Defines a sphere.
     */
    class BoundingSphere
    {
    public:

        /**
         * @brief Creates a new instance of BoundingSphere.
         * @param center = Center point of the sphere.
         * @param radius = Radius of the sphere.
         */
        BoundingSphere(const vec3f center, const float radius);

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
