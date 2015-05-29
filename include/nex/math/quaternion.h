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

        /**
         * it's called only when U != T.
         * A call to this constructor will fail to compile if U
         * is not convertible to T.
         */
        template <typename U>
        explicit Quaternion(const Quaternion<U>& vector);

        T& operator=(const T& lhs) & {
            x = lhs.x;
            y = lhs.y;
            z = lhs.z;
            w = lhs.w;
            return *this;
        }

        /**
         * @brief Calculates the length of a Quaternion.
         * @return the length.
         */
        T length() const;

        /**
         * @brief Calculates the length squared of a Quaternion.
         * @return the length squared.
         */
        T lengthSquared() const;

        /**
         * @brief Divides each component of the quaternion by the length of the quaternion.
         */
        void normalize();

        /**
         * @brief Divides each component of the quaternion by the length of the quaternion.
         * @param value = the quaternion to normalize.
         * @return the normalized quaternion.
         */
        static Quaternion<T> normalize(const Quaternion& value);

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
