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

        /**
         * @brief calculates the distances between two vectors.
         * @param other = the other vector.
         * @return the distance between them.
         */
        T distance(const Vec3<T>& other) const;

        /**
         * @brief calculates the distance squared between two vectors.
         * @param other = the other vector.
         * @return the distance between them.
         */
        T distanceSquared(const Vec3<T>& other) const;

        /**
         * @brief Calculates the dot product of two vectors.
         * @param other = the other vector to use.
         * @return the dot product between the vectors.
         */
        T dot(const Vec3<T>& other) const;

        /**
         * @brief Calculates the cross product of two vectors.
         * @param other = other vector to use.
         * @return the cross product.
         */
        Vec3<T> cross(const Vec3<T>& other) const;

        /**
         * @brief normalize this vector into a unit vector.
         */
        void normalize();

        /**
         * @brief Creates a unit vector from the specified vector.
         * @param vector = vector to convert.
         * @return unit vector.
         */
        static Vec3<T> normalize(const Vec3<T>& vector);

        /**
         * @brief calculates the distances between two vectors.
         * @param vectorA = the first vector.
         * @param vectorB = the second vector.
         * @return the distance between them.
         */
        static T distance(const Vec3<T>& vectorA, const Vec3<T>& vectorB);

        /**
         * @brief calculates the distance squared between two vectors.
         * @param vectorA = the first vector.
         * @param vectorB = the second vector.
         * @return the distance between them.
         */
        static T distanceSquared(const Vec3<T>& vectorA, const Vec3<T>& vectorB);

        /**
         * @brief Calculates the dot product of two vectors.
         * @param vectorA = first vector.
         * @param vectorB = second vector.
         * @return the dot product of the two vectors.
         */
        static T dot(const Vec3<T>& vectorA, const Vec3<T>& vectorB);

        /**
         * @brief Calculates the cross product of two vectors.
         * @param vectorA
         * @param vectorB
         * @return
         */
        static Vec3<T> cross(const Vec3<T>& vectorA, const Vec3<T>& vectorB);

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
