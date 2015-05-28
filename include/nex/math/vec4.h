#ifndef VEC4_H_INCLUDE
#define VEC4_H_INCLUDE

namespace nx
{
    template <typename T>
    class Vec4
    {
    public:

        /**
         * @brief Constructs a zero vector.
         */
        Vec4();

        /**
         * @brief Constructs a vector with the given value.
         * @param value = value to set.
         */
        Vec4(T value);

        /**
         * @brief construct a vector with the given values.
         * @param x = x coordinate.
         * @param y = y coordinate.
         * @param z = z coordinate.
         * @param w = w corrdinate.
         */
        Vec4(T x, T y, T z, T w);

        /**
         * it's called only when U != T.
         * A call to this constructor will fail to compile if U
         * is not convertible to T.
         */
        template <typename U>
        explicit Vec4(const Vec4<U>& vector);

        //Vector copy.
        T& operator=(const T& lhs) & {
            x = lhs.x;
            y = lhs.y;
            z = lhs.z;
            w = lhs.w;
            return *this;
        }

        T x;
        T y;
        T z;
        T w;
    };

#include <nex/math/vec4.inl>

    typedef Vec4<int> vec4i;
    typedef Vec4<int> vec4u;
    typedef Vec4<float> vec4f;
    typedef Vec4<double> vec4d;
} //namespace nx

#endif
