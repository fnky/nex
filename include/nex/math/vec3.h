#ifndef VEC3_H_INCLUDE
#define VEC3_H_INCLUDE

//Nex includes.
#include <nex/system/typedefs.h>

namespace nx
{
    template <typename T>
    class Vec3
    {
    public:

        /**
         * @brief Constructs a zero vector.
         */
        Vec3();

        /**
         * @brief Constructs a vector with the given value.
         * @param value = value to set.
         */
        Vec3(T value);

        /**
         * @brief construct a vector with the given values.
         * @param x = x coordinate.
         * @param y = y coordinate.
         * @param z = z coordinate.
         */
        Vec3(T x, T y, T z);


        /**
         * it's called only when U != T.
         * A call to this constructor will fail to compile if U
         * is not convertible to T.
         */
        template <typename U>
        explicit Vec3(const Vec3<U>& vector);

        //Vector copy.
        T& operator=(const T& lhs) & {
            x = lhs.x;
            y = lhs.y;
            z = lhs.z;
            return *this;
        }


        /**
         * @brief calculates the length of the vector.
         * @return vector length.
         */
        T length() const;

        /**
         * @brief calculates the squared length of the vector.
         * @return squared vector length.
         */
        T lengthSquared() const;

        T x;
        T y;
        T z;
    };

#include <nex/math/vec3.inl>

    typedef Vec3<int> vec3i;
    typedef Vec3<int> vec3u;
    typedef Vec3<float> vec3f;
    typedef Vec3<double> vec3d;

} //namespace nx

#endif // VEC3_H_INCLUDE
