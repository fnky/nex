#ifndef QUATERNION_H_INCLUDE
#define QUATERNION_H_INCLUDE

namespace nx
{
    template <typename T>
    class Quaternion
    {
    public:

        /**
         * @brief Construct an identity matrix.
         */
        Quaternion();

        /**
         * @brief Construct a quaternion with the specified values.
         * @param x = x value.
         * @param y = y value.
         * @param z = z value.
         * @param w = w value.
         */
        Quaternion(const T x, const T y, const T z, const T w);

        T x;
        T y;
        T z;
        T w;
    };

#include <nex/math/quaternion.inl>

    typedef Quaternion<float> quatf;
    typedef Quaternion<double> quatd;

} // namespace nx

#endif // QUATERNION_H_INCLUDE
