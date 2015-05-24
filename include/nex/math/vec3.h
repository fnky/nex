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
         * @param vectorA = source vector
         * @param vectorB = source vector
         * @return the cross product of the vectors.
         */
        static Vec3<T> cross(const Vec3<T>& vectorA, const Vec3<T>& vectorB);

        /**
         * @brief Returns the reflection of a vector off a surface that has the specified normal.
         * @param vector = Source vector.
         * @param normal = Normal of the surface.
         * @return the reflected vector.
         */
        static Vec3<T> reflect(const Vec3<T>& vector, const Vec3<T>& normal);

        /**
         * @brief Returns a vector that contains the lowest value from each matching pair of components.
         * @param vectorA = Source vector.
         * @param vectorA = source vector.
         * @return the min values from the pair.
         */
        static Vec3<T> min(const Vec3<T>& vectorA, const Vec3<T>& vectorB);

        /**
         * @brief Returns a vector that contains the heighest value from each matching pair of components.
         * @param vectorA = Source vector.
         * @param vectorA = source vector.
         * @return the max values from the pair.
         */
        static Vec3<T> max(const Vec3<T>& vectorA, const Vec3<T>& vectorB);

        /**
         * @brief Restricts a value to be within a specified range.
         * @param value = value to apply clamping to.
         * @param min = minimum value allowed.
         * @param max = maximum value allowed.
         * @return the restricted value.
         */
        static Vec3<T> clamp(const Vec3<T>& value, const Vec3<T>& min, const Vec3<T>& max);

        /**
         * @brief Performs a linear interpolation between two vectors.
         * @param previous = previous vector value.
         * @param current = current vector value.
         * @param amount = Value between 0 and 1 indicating the weight of value2.
         * @return the linear interpolation of the vectors.
         */
        static Vec3<T> lerp(const Vec3<T>& previous, const Vec3<T>& current, const T amount);

        /**
         * @brief Returns a Vector3 containing the 3D Cartesian coordinates of a point specified in Barycentric coordinates relative to a 3D triangle.
         * @param vertexA = source vertex.
         * @param vertexB = source vertex.
         * @param vertexC = source vertex.
         * @param weightA = weight for vertex a
         * @param weightB = weight for vertex b
         * @return
         */
        static Vec3<T> barycentric(const Vec3<T>& vertexA, const Vec3<T>& vertexB, const Vec3<T>& vertexC, const T weightA, const T weightB);

        /**
         * @brief Interpolates between two values using a cubic equation.
         * @param previous = previous vector value.
         * @param current = current vector value.
         * @param amount = weight of the value.
         * @return the interpolated value.
         */
        static Vec3<T> smoothStep(const Vec3<T>& previous, const Vec3<T>& current, T amount);

        /**
         * @brief Performs a Catmull-Rom interpolation using the specified positions.
         * @param vertexA = first source vertex.
         * @param vertexB = second source vertex.
         * @param vertexC = third source vertex.
         * @param vertexD = forth source vertex.
         * @param amount = weight to apply on the vertices.
         * @return the interpolated vertex.
         */
        static Vec3<T> catmullRom(const Vec3<T>& vertexA, const Vec3<T>& vertexB, const Vec3<T>& vertexC, const Vec3<T>& vertexD, const T amount);

        /**
         * @brief Performs a Hermite spline interpolation.
         * @param vertexA = first source vertex.
         * @param tangentA = first tangent vector.
         * @param vertexB = second source vertex.
         * @param tangentB = second tangent vector.
         * @param amount = weight to apply during the interpolation.
         * @return the interpolated vector.
         */
        static Vec3<T> hermite(const Vec3<T>& vertexA, const Vec3<T>& tangentA, const Vec3<T>& vertexB, const Vec3<T>& tangentB, const T amount);

        /**
         * TODO (Tyler): Implement the following methods:
         * - static Vector3 Transform(Vector3 position, Matrix matrix)
         * - static Vector3 TransformNormal(Vector3 normal, Matrix matrix)
         * - static Vector3 Transform(Vector3 value, Quaternion rotation)
         * - static void Transform(Vector3[] sourceArray, ref Matrix matrix, Vector3[] destinationArray)
         * - static void Transform(Vector3[] sourceArray, int sourceIndex, ref Matrix matrix, Vector3[] destinationArray, int destinationIndex, int length)
         * - static void TransformNormal(Vector3[] sourceArray, int sourceIndex, ref Matrix matrix, Vector3[] destinationArray, int destinationIndex, int length)
         * - static void Transform(Vector3[] sourceArray, int sourceIndex, ref Quaternion rotation, Vector3[] destinationArray, int destinationIndex, int length)
         */

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
