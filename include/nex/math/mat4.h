#ifndef MATRIX_H_INCLUDE
#define MATRIX_H_INCLUDE

namespace nx
{
    template <typename T>

    class Mat4
    {
    public:

        // Value at row 1 column 1 of the matrix.
        T M11;

        // Value at row 1 column 2 of the matrix.
        T M12;

        // Value at row 1 column 3 of the matrix.
        T M13;

        // Value at row 1 column 4 of the matrix.
        T M14;

        // Value at row 2 column 1 of the matrix.
        T M21;

        // Value at row 2 column 2 of the matrix.
        T M22;

        // Value at row 2 column 3 of the matrix.
        T M23;

        // Value at row 2 column 4 of the matrix.
        T M24;

        // Value at row 3 column 1 of the matrix.
        T M31;

        // Value at row 3 column 2 of the matrix.
        T M32;

        // Value at row 3 column 3 of the matrix.
        T M33;

        // Value at row 3 column 4 of the matrix.
        T M34;

        // Value at row 4 column 1 of the matrix.
        T M41;

        // Value at row 4 column 2 of the matrix.
        T M42;

        // Value at row 4 column 3 of the matrix.
        T M43;

        // Value at row 4 column 4 of the matrix.
        T M44;
    };

#include <nex/math/mat4.inl>

    typedef Mat4<float> mat4f;
    typedef Mat4<double> mat4d;

} //namespace nx

#endif // MATRIX_H_INCLUDE
