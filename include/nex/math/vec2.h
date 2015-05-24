#ifndef VEC2_H_INCLUDE
#define VEC2_H_INCLUDE

//Nex project includes.
#include <nex/system/typedefs.h>

namespace nx
{
    template <typename T>

    class Vec2
    {
    public:

        /**
         * @brief default constructor. zeros out the values.
         */
        Vec2();

        /**
         * @brief construct a vector with both x and y set to the same value.
         * @param value = value to set x and y to.
         */
        Vec2(T value);

        /**
         * @brief construct a vector with the given values.
         * @param x = x coordinate.
         * @param y = y coordinate.
         */
        Vec2(T x, T y);


        /**
         * it's called only when U != T.
         * A call to this constructor will fail to compile if U
         * is not convertible to T.
         */
        template <typename U>
        explicit Vec2(const Vec2<U>& vector);

        T& operator=(const T& lhs) & {
            x = lhs.x;
            y = lhs.y;
            return *this;
        }

        /**
         * @brief normalize the current vector.
         */
        void normalize();

        /**
         * @brief normalize the given vector.
         * @param value = vector to make normal.
         * @return returns the normal vector.
         */
        static Vec2<T> normalize(const Vec2<T>& value);

        /**
         * @brief calculate the length of the given vector.
         * @return the length of the vector.
         */
        T length() const;

        /**
         * @brief calculate the length squared of the given vector.
         * @return the length squared.
         */
        T lengthSquared() const;

        /**
         * @brief calculates the distance between two vectors using the distance formula.
         * @param left = left vector
         * @param right = right vector
         * @return the distance between the two vectors.
         */
        static T distance(const Vec2<T>& left, const Vec2<T>& right);

        /**
         * @brief calculate the distance to another given vector.
         * @param other = other vector
         * @return distance between the two vectors.
         */
        T distance(const Vec2<T>& other) const;

         /**
          * @brief calculate the distance squared between two given vector.s
          * @param left = left vector
          * @param right = right vector
          * @return distance squared between the vectors.
          */
        static T distanceSquared(const Vec2<T>& left, const Vec2<T>& right);

        /**
         * @brief calculate the squared sitance between the given vectors.
         * @param other = other vector
         * @return distance squared between the given vectors.
         */
        T distanceSquared(const Vec2<T>& other) const;

        /**
         * @brief calculate the dot product of two vectors.
         * @param left = left vector
         * @param right = right vector
         * @return the dot product returns a floating point value between -1 and 1.
         */
        static T dot(const Vec2<T>& left, const Vec2<T>& right);

        /**
         * @brief calculate the dot product of two vectors.
         * @param other = other vector
         * @return the dot product returns a floating point value between -1 and 1.
         */
        T dot(const Vec2<T>& other);

        //X value.
        T x;

        //Y value.
        T y;
    };

    //define some common vector types.

#include <nex/math/vec2.inl>

    typedef nx::Vec2<int32> vec2i;

    typedef nx::Vec2<uint32> vec2u;

    typedef nx::Vec2<float> vec2f;

    typedef nx::Vec2<double> vec2d;

} //namespace nx

#endif // VEC2_H_INCLUDE
