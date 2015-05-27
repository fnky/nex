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

        //Our matrix data.
        row_type m[4];
    };

#include <nex/math/matrix.inl>

} //namespace nx

#endif // MATRIX_H_INCLUDE
