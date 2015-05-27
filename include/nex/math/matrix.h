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

    typedef float row_type[4];

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
         * @param fieldOfView = Field of view in the y direction, in radians.
         * @param aspectRatio = Aspect ratio, defined as view space width divided by height. To match the aspect ratio of the viewport.
         * @param nearPlaneDistance = Distance to the near view plane.
         * @param farPlaneDistance = Distance to the far view plane.
         * @return the perspective matrix.
         */
        static Matrix createPerspectiveFieldOfView(
                const float fieldOfView,
                const float aspectRatio,
                const float nearPlaneDistance,
                const float farPlaneDistance);

        /**
         * @brief Builds a perspective projection matrix and returns the result by value.
         * @param width = Width of the view volume at the near view plane.
         * @param height = Height of the view volume at the near view plane.
         * @param nearPlaneDistance = Distance to the near view plane.
         * @param farPlaneDistance = Distance to the far view plane.
         * @return
         */
        static Matrix createPerspective(const float width,
                                        const float height,
                                        const float nearPlaneDistance,
                                        const float farPlaneDistance);

        /**
         * @brief Builds a customized, perspective projection matrix.
         * @param left = Minimum x-value of the view volume at the near view plane.
         * @param right = Maximum x-value of the view volume at the near view plane.
         * @param bottom = Minimum y-value of the view volume at the near view plane.
         * @param top = Maximum y-value of the view volume at the near view plane.
         * @param nearPlaneDistance = Distance to the near view plane.
         * @param farPlaneDistance = Distance to the far view plane.
         * @return the perspective projection matrix.
         */
        static Matrix createPerspectiveOffCenter(
                const float left,
                const float right,
                const float bottom,
                const float top,
                const float nearPlaneDistance,
                const float farPlaneDistance);

        /**
         * @brief Builds an orthogonal projection matrix.
         * @param width = Width of the view volume.
         * @param height = Height of the view volume.
         * @param zNearPlane = Minimum z-value of the view volume.
         * @param zFarPlane = Maximum z-value of the view volume.
         * @return the orthoganal projection matrix.
         */
        static Matrix createOrthographic(
                const float width,
                const float height,
                const float zNearPlane,
                const float zFarPlane);

        /**
         * @brief Builds a customized, orthogonal projection matrix.
         * @param left = Minimum x-value of the view volume.
         * @param right = Maximum x-value of the view volume.
         * @param bottom = Minimum y-value of the view volume.
         * @param top = Maximum y-value of the view volume.
         * @param zNearPlane = Minimum z-value of the view volume.
         * @param zFarPlane = Maximum z-value of the view volume.
         * @return the orthagonal projection matrix.
         */
        static Matrix createOrthographicOffCenter(
                const float left,
                const float right,
                const float bottom,
                const float top,
                const float zNearPlane,
                const float zFarPlane);

        /**
         * @brief Creates a view matrix.
         * @param cameraPosition = The position of the camera.
         * @param cameraTarget = The target towards which the camera is pointing.
         * @param cameraUpVector = The direction that is "up" from the camera's point of view.
         * @return the view matrix.
         */
        static Matrix createLookAt(const vec3f& cameraPosition, const vec3f& cameraTarget, const vec3f& cameraUpVector);

        /**
         * @brief Creates a scaling Matrix.
         * @param xScale = Value to scale by on the x-axis.
         * @param yScale = Value to scale by on the y-axis.
         * @param zScale = Value to scale by on the z-axis.
         * @return the scale matrix.
         */
        static Matrix scale(const float xScale, const float yScale, const float zScale);

        /**
         * @brief Creates a spherical billboard that rotates around a specified object position.
         * @param objectPosition = Position of the object the billboard will rotate around.
         * @param cameraPosition = Position of the camera.
         * @param cameraUpVector = The up vector of the camera.
         * @param cameraForwardVector = Forward vector of the camera.
         * @return the matrix for the billboard.
         */
        static Matrix createBillboard(const vec3f& objectPosition,
                                      const vec3f& cameraPosition,
                                      const vec3f& cameraUpVector,
                                      const vec3f& cameraForwardVector);

        /**
         * @brief Creates a cylindrical billboard that rotates around a specified axis.
         * @param objectPosition = Position of the object the billboard will rotate around.
         * @param cameraPosition = Position of the camera.
         * @param rotateAxis = Axis to rotate the billboard around.
         * @param cameraForwardVector = Forward vector of the camera.
         * @param objectForwardVector = Forward vector of the object.
         * @return
         */
        static Matrix createConstrainedBillboard(const vec3f& objectPosition,
                                                 const vec3f& cameraPosition,
                                                 const vec3f& rotateAxis,
                                                 const vec3f& cameraForwardVector,
                                                 const vec3f& objectForwardVector);

        //Our matrix data.
        row_type m[4];
    };

#include <nex/math/matrix.inl>

} //namespace nx

#endif // MATRIX_H_INCLUDE
