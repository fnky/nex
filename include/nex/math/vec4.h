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
         * @brief Calculates the dot product of two vectors.
         * @param left = Left source vector.
         * @param right = right source vector.
         * @return the dot product of the vectors.
         */
        T dot(const Vec4<T>& other) const;

        /**
         * @brief Turns the current vector into a unit vector.
         */
        void normalize();

        /**
         * @brief Calculates the distance between two vectors.
         * @param left = Left source vector.
         * @param right = right source vector.
         * @return the distance between the given vectors.
         */
        static T distance(const Vec4<T>& left, const Vec4<T>& right);

        /**
         * @brief Calculates the distance squared between two vectors.
         * @param left = Left source vector.
         * @param right = right source vector.
         * @return the distance squared between the given vectors.
         */
        static T distanceSquared(const Vec4<T>& left, const Vec4<T>& right);

        /**
         * @brief Calculates the dot product of two vectors.
         * @param left = Left source vector.
         * @param right = right source vector.
         * @return the dot product of the vectors.
         */
        static T dot(const Vec4<T>& left, const Vec4<T>& right);

        /**
         * @brief Turns the specifed vector into a unit vector.
         * @param value = vector to normalize
         * @return unit vector.
         */
        static Vec4<T> normalize(const Vec4<T>& value);

        /**
         * @brief Returns a vector that contains the lowest value from each matching pair of components.
         * @param left = left source vector.
         * @param right = right source vector.
         * @return the min values.
         */
        static Vec4<T> min(const Vec4<T>& left, const Vec4<T>& right);

        /**
         * @brief Returns a vector that contains the heighest value from each matching pair of components.
         * @param left = left source vector.
         * @param right = right source vector.
         * @return the max values.
         */
        static Vec4<T> max(const Vec4<T>& left, const Vec4<T>& right);

        /**
         * @brief Restricts a value to be within a specified range.
         * @param value = The value to restrict.
         * @param min = the minimum value.
         * @param max = the maximum value.
         * @return the clamped vector.
         */
        static Vec4<T> clamp(const Vec4<T>& value, const Vec4<T>& min, const Vec4<T>& max);

        /**
         * @brief Performs a linear interpolation between two vectors.
         * @param previous = previous value.
         * @param current = current value.
         * @param amount = amount to interpolate by.
         * @return the interpolated vector.
         */
        static Vec4<T> lerp(const Vec4<T>& previous, const Vec4<T>& current, const T amount);

        /**
         * @brief Returns a Vector4 containing the 4D Cartesian coordinates of a point specified in barycentric (areal) coordinates relative to a 4D triangle.
         * @param vertexA = A Vector4 containing the 4D Cartesian coordinates of vertex 1 of the triangle.
         * @param vertexB = A Vector4 containing the 4D Cartesian coordinates of vertex 2 of the triangle.
         * @param vertexC = A Vector4 containing the 4D Cartesian coordinates of vertex 3 of the triangle.
         * @param weightA = Barycentric coordinate b2, which expresses the weighting factor toward vertex 2 (specified in value2).
         * @param weightB = Barycentric coordinate b3, which expresses the weighting factor toward vertex 3 (specified in value3).
         * @return the 4D Cartesian coordinates
         */
        static Vec4<T> barycentric(
                const Vec4<T>& vertexA,
                const Vec4<T>& vertexB,
                const Vec4<T>& vertexC, const T weightA, const T weightB);

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
