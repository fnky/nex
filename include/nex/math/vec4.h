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

        /**
         * @brief Calculates the length of the vector.
         * @return vector length.
         */
        T length() const;

        /**
         * @brief Calculates the length squared of the vector.
         * @return vector squared length.
         */
        T lengthSquared() const;

        /**
         * @brief Calculates the distance between two vectors.
         * @param other = the other source vector.
         * @return the distance between this and the other vector.
         */
        T distance(const Vec4<T>& other) const;

        /**
         * @brief Calculates the distance squared between two vectors.
         * @param other = the other source vector.
         * @return the distance squared between this and the other vector.
         */
        T distanceSquared(const Vec4<T>& other) const;

        /**
         * @brief Calculates the distance between two vectors.
         * @param left = Left source vector.
         * @param right = right source vector.
         * @return the distance between the given vectors.
         */
        static float distance(const Vec4<T>& left, const Vec4<T>& right);

        /**
         * @brief Calculates the distance squared between two vectors.
         * @param left = Left source vector.
         * @param right = right source vector.
         * @return the distance squared between the given vectors.
         */
        static float distanceSquared(const Vec4<T>& left, const Vec4<T>& right);

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
