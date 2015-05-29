#ifndef RAY_H_INCLUDE
#define RAY_H_INCLUDE

#include <nex/math/vec3.h>

namespace nx
{
    class Ray
    {
    public:

        /**
         * @brief Constructs a ray.
         * @param position = postition of the ray.
         * @param direction = unit vector direction.
         */
        Ray(vec3f position, vec3f direction);

        /**
         * @brief Specifies the starting point of the Ray.
         */
        vec3f position;

        /**
         * @brief Unit vector specifying the direction the Ray is pointing.
         */
        vec3f direction;
    };

#include <nex/math/ray.inl>

} //namespace nx

#endif
