#ifndef MATRIX_H_INCLUDE
#define MATRIX_H_INCLUDE

//Nex includes.
#include <nex/system/typedefs.h>

#ifndef VEC2_H_INCLUDE
#include "vec2.h"
#endif

#ifndef VEC3_H_INCLUDE
#include "vec3.h"
#endif

#ifndef VEC4_H_INCLUDE
#include "vec4.h"
#endif

/*
 * TODO (Tyler): Implement the following.
 *
 * - public static Vector2 TransformNormal(Vector2 normal, Matrix matrix)
 * - public static Vector2 Transform(Vector2 value, Quaternion rotation)
 * - static Vector3 Transform(Vector3 position, Matrix matrix)
 * - static Vector3 TransformNormal(Vector3 normal, Matrix matrix)
 * - static Vector3 Transform(Vector3 value, Quaternion rotation)
 *
 * - frustum
 * - infinite perspective
 * - lookAt
 * - pickMatrix
 * - project
 * - unproject
 *
 * GLM Reference:
 * http://glm.g-truc.net/0.9.2/api/a00245.html
 */

namespace nx
{
    // The elements of the matrix are stored as column major order.
    // |  0  4  8 12 |
    // |  1  5  9 13 |
    // |  2  6 10 14 |
    // |  3  7 11 15 |

    //This is how we address the matrix.
    //| m11 m12 m13 m14 |
    //| m21 m22 m23 m24 |
    //| m31 m32 m33 m34 |
    //| m41 m42 m43 m44 |

    //This is how the values are layed out in memory.
    //m11 m21 m31 m41 m12 m22 m32 m42 m13 m23 m33 m43 m14 m24 m34 m44

    //So that means we store our translation in the far right column.
    //| 1 0 0 x |
    //| 0 1 0 y |
    //| 0 0 1 z |
    //| 0 0 0 1 |

    typedef float col_type[4];

    class Matrix
    {
    public:

        /**
         * @brief Constructs an identity matrix.
         */
        Matrix();

        /**
         * @brief Create a matrix with the specified values.
         */
        Matrix(const float m11, const float m21, const float m31, const float m41,
               const float m12, const float m22, const float m32, const float m42,
               const float m13, const float m23, const float m33, const float m43,
               const float m14, const float m24, const float m34, const float m44);

        /**
         * @brief Returns the address to the array data.
         * @return the pointer to the data.
         */
        inline float* getPtr() { return (float*)&m; }

        /**
         * @brief Allows the users of this class to access the interal values by [y][x] as needed.
         * @param index to lookup.
         * @return pointer to the data.
         */
        row_type& operator[] (const uint32 index);

        /**
         * @brief Allows the users of this class to access the interal values by [y][x] as needed.
         * @param index to lookup.
         * @return pointer to the data.
         */
        const row_type& operator[] (const uint32 index) const;

        /**
         * @brief Create a translation matrix.
         * @param position = position to translate to.
         * @return the translation matrix.
         */
        static Matrix translate(const vec3f& position);

        /**
         * @brief Returns a matrix that can be used to rotate a set of vertices around the x-axis.
         * @param radians = The amount, in radians, in which to rotate around the x-axis.
         * @return the rotation matrix.
         */
        static Matrix rotateX(const float radians);

        /**
         * @brief Returns a matrix that can be used to rotate a set of vertices around the y-axis.
         * @param radians = the amount, in radians, in which to rotate around the y-axis.
         * @return the rotation matrix.
         */
        static Matrix rotateY(const float radians);

        /**
         * @brief Returns a matrix that can be used to rotate a set of vertices around the z-axis.
         * @param radians = the amount, in radians, in which to rotate around the z-axis.
         * @return the rotation matrix.
         */
        static Matrix rotateZ(const float radians);

        /**
         * @brief Creates a new Matrix that rotates around an arbitrary vector.
         * @param axis = The axis to rotate around.
         * @param angle = The angle to rotate around the vector in radians.
         * @return the rotation matrix.
         */
        static Matrix createFromAxisAngle(const vec3f& axis, const float angle);

        /**
         * @brief Builds a perspective projection matrix based on a field of view and returns by value.
         * @param fovy = Field of view in the y direction, in radians.
         * @param aspect = Aspect ratio, defined as view space width divided by height. To match the aspect ratio of the viewport.
         * @param zNear = Distance to the near view plane.
         * @param zFar = Distance to the far view plane.
         * @return the perspective matrix.
         */
        static Matrix perspective(
                const float fovy,
                const float aspect,
                const float zNear,
                const float zFar);

        /**
         * @brief Builds a perspective projection matrix based on a field of view
         * @param fov = Field of view in the y direction, in radians.
         * @param width = Width of the view volume at the near view plane.
         * @param height = Height of the view volume at the near view plane.
         * @param zNear = Distance to the near view plane.
         * @param zFar =  Distance to the far view plane.
         * @returnthe perspective matrix.
         */
        static Matrix perspectiveFov(
                const float fov,
                const float width,
                const float height,
                const float zNear,
                const float zFar);

        /**
         * @brief Builds an orthogonal projection matrix.
         * @param width = Width of the view volume.
         * @param height = Height of the view volume.
         * @param zNearPlane = Minimum z-value of the view volume.
         * @param zFarPlane = Maximum z-value of the view volume.
         * @return the orthoganal projection matrix.
         */
        static Matrix orthographic(
                const float width,
                const float height,
                const float zNearPlane,
                const float zFarPlane);
        /**
         * @brief Creates a scaling Matrix.
         * @param xScale = Value to scale by on the x-axis.
         * @param yScale = Value to scale by on the y-axis.
         * @param zScale = Value to scale by on the z-axis.
         * @return the scale matrix.
         */
        static Matrix scale(const float xScale, const float yScale, const float zScale);

        //Our matrix data.
        col_type m[4];
    };

#include <nex/math/matrix.inl>

} //namespace nx

#endif // MATRIX_H_INCLUDE
