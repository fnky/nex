#ifndef MATRIX_H_INCLUDE
#define MATRIX_H_INCLUDE

//Nex includes.
#include <nex/system/typedefs.h>

#include <nex/math/vec2.h>
#include <nex/math/vec3.h>
#include <nex/math/vec4.h>

/*
 * TODO (Tyler): Implement the following.
 *
 * - static Vector2 TransformNormal(Vector2 normal, Matrix matrix)
 * - static Vector2 Transform(Vector2 value, Quaternion rotation)
 *
 * - static Vector3 Transform(Vector3 position, Matrix matrix)
 * - static Vector3 TransformNormal(Vector3 normal, Matrix matrix)
 * - static Vector3 Transform(Vector3 value, Quaternion rotation)
 *
 * - static Vector4 Transform(Vector4 vector, Matrix matrix)
 * - static Vector4 Transform(Vector4 value, Quaternion rotation)
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
// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
//            | 2 5 8 |    |  2  6 10 14 |
//                         |  3  7 11 15 |

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

//friend Vector3 operator*(const Vector3& vec, const Matrix4& m);
//friend Vector4 operator*(const Vector4& vec, const Matrix4& m);
template <typename T>
class Matrix
{
public:

    typedef T col_type[4];
    /**
     * @brief Constructs an identity matrix.
     */
    Matrix();

    /**
     * @brief Create a matrix with the specified values.
     */
    Matrix(const T m11, const T m21, const T m31, const T m41,
           const T m12, const T m22, const T m32, const T m42,
           const T m13, const T m23, const T m33, const T m43,
           const T m14, const T m24, const T m34, const T m44);

    //Matrix copy.
    Matrix& operator=(const Matrix& lhs) & {

        m[0][0] = lhs[0][0];
        m[0][1] = lhs[0][1];
        m[0][2] = lhs[0][2];
        m[0][3] = lhs[0][3];

        m[1][0] = lhs[1][0];
        m[1][1] = lhs[1][1];
        m[1][2] = lhs[1][2];
        m[1][3] = lhs[1][3];

        m[2][0] = lhs[2][0];
        m[2][1] = lhs[2][1];
        m[2][2] = lhs[2][2];
        m[2][3] = lhs[2][3];

        m[3][0] = lhs[3][0];
        m[3][1] = lhs[3][1];
        m[3][2] = lhs[3][2];
        m[3][3] = lhs[3][3];

        return *this;
    }

    /**
     * @brief Returns the address to the array data.
     * @return the pointer to the data.
     */
    inline T* getPtr() { return (T*)&m; }

    /**
     * @brief Allows the users of this class to access the interal values by [y][x] as needed.
     * @param index to lookup.
     * @return pointer to the data.
     */
    col_type& operator[] (const uint32 index);

    /**
     * @brief Allows the users of this class to access the interal values by [y][x] as needed.
     * @param index to lookup.
     * @return pointer to the data.
     */
    const col_type& operator[] (const uint32 index) const;

    /**
     * @brief Create a translation matrix.
     * @param position = position to translate to.
     * @return the translation matrix.
     */
    static Matrix translate(const Vec3<T>& position);

    /**
     * @brief Returns a matrix that can be used to rotate a set of vertices around the x-axis.
     * @param radians = The amount, in radians, in which to rotate around the x-axis.
     * @return the rotation matrix.
     */
    static Matrix rotateX(const T radians);

    /**
     * @brief Returns a matrix that can be used to rotate a set of vertices around the y-axis.
     * @param radians = the amount, in radians, in which to rotate around the y-axis.
     * @return the rotation matrix.
     */
    static Matrix rotateY(const T radians);

    /**
     * @brief Returns a matrix that can be used to rotate a set of vertices around the z-axis.
     * @param radians = the amount, in radians, in which to rotate around the z-axis.
     * @return the rotation matrix.
     */
    static Matrix rotateZ(const T radians);

    /**
     * @brief Creates a new Matrix that rotates around an arbitrary vector.
     * @param axis = The axis to rotate around.
     * @param angle = The angle to rotate around the vector in radians.
     * @return the rotation matrix.
     */
    static Matrix createFromAxisAngle(const Vec3<T>& axis, const T angle);

    /**
     * @brief Creates a new frustum matrix.
     * @param left = Left plane.
     * @param right = Right plane.
     * @param bottom = Bottom plane.
     * @param top = Top plane.
     * @param nearVal = The near plane value.
     * @param farVal = the far plane value.
     * @return the new frustum matrix.
     */
    static Matrix frustum(
            const T left,
            const T right,
            const T bottom,
            const T top,
            const T nearVal,
            const T farVal
        );

    /**
     * @brief Creates a scaling Matrix.
     * @param xScale = Value to scale by on the x-axis.
     * @param yScale = Value to scale by on the y-axis.
     * @param zScale = Value to scale by on the z-axis.
     * @return the scale matrix.
     */
    static Matrix scale(const T xScale, const T yScale, const T zScale);

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

    //Our matrix data.
    col_type m[4];

}; //class matrix

#include <nex/math/matrix.inl>

} //namespace nx

#endif // MATRIX_H_INCLUDE
