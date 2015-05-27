#include <cmath>

inline Matrix::Matrix()
{
    //Create an identity matrix.
    m[0][0] = 1.0f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;

    m[1][0] = 0.0f;
    m[1][1] = 1.0f;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 1.0f;
    m[2][3] = 0.0f;

    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
}

inline Matrix::Matrix(const float m11, const float m21, const float m31, const float m41,
       const float m12, const float m22, const float m32, const float m42,
       const float m13, const float m23, const float m33, const float m43,
       const float m14, const float m24, const float m34, const float m44)
{
    m[0][0] = m11;
    m[1][0] = m21;
    m[2][0] = m31;
    m[3][0] = m41;

    m[0][1] = m12;
    m[1][1] = m22;
    m[2][1] = m32;
    m[3][1] = m42;

    m[0][2] = m13;
    m[1][2] = m23;
    m[2][2] = m33;
    m[3][2] = m43;

    m[0][3] = m14;
    m[1][3] = m24;
    m[2][3] = m34;
    m[3][3] = m44;
}

inline row_type& Matrix::operator[] (const uint32 index)
{
    return m[index];
}

inline Matrix Matrix::createBillboard(
        const vec3f& objectPosition,
        const vec3f& cameraPosition,
        const vec3f& cameraUpVector,
        const vec3f& cameraForwardVector)
{
    vec3f delta;
    delta.x = objectPosition.x - cameraPosition.x;
    delta.y = objectPosition.y - cameraPosition.y;
    delta.z = objectPosition.z - cameraPosition.z;

    const float vectorLength = delta.lengthSquared();

    //Make sure we are in the proper range.
    if ((double) vectorLength < 9.99999974737875E-05) {
        delta = -cameraForwardVector;
    }
    else {
        delta = delta * 1.0f / static_cast<float>(sqrt(vectorLength));
    }

    vec3f result2 = vec3f::cross(cameraUpVector, delta);

    result2.normalize();

    vec3f result3 = vec3f::cross(delta, result2);

    Matrix matrix;

    matrix[0][0] = result2.x;
    matrix[0][1] = result2.y;
    matrix[0][2] = result2.z;
    matrix[0][3] = 0.0f;

    matrix[1][0] = result3.x;
    matrix[1][1] = result3.y;
    matrix[1][2] = result3.z;
    matrix[1][3] = 0.0f;

    matrix[2][0] = delta.x;
    matrix[2][1] = delta.y;
    matrix[2][2] = delta.z;
    matrix[2][3] = 0.0f;

    matrix[3][0] = objectPosition.x;
    matrix[3][1] = objectPosition.y;
    matrix[3][2] = objectPosition.z;
    matrix[3][2] = 1.0f;

    return matrix;
}

inline Matrix operator -( Matrix& right)
{
    return Matrix(
            -right[0][0], -right[1][0], -right[2][0], -right[3][0],
            -right[0][1], -right[1][1], -right[2][1], -right[3][1],
            -right[0][2], -right[1][2], -right[2][2], -right[3][2],
            -right[0][3], -right[1][3], -right[2][3], -right[3][3]);

}

inline Matrix& operator +=(Matrix& left, Matrix& right)
{
    left[0][0] += right[0][0];
    left[0][1] += right[0][1];
    left[0][2] += right[0][2];
    left[0][3] += right[0][3];

    left[1][0] += right[1][0];
    left[1][1] += right[1][1];
    left[1][2] += right[1][2];
    left[1][3] += right[1][3];

    left[2][0] += right[2][0];
    left[2][1] += right[2][1];
    left[2][2] += right[2][2];
    left[2][3] += right[2][3];

    left[3][0] += right[3][0];
    left[3][1] += right[3][1];
    left[3][2] += right[3][2];
    left[3][3] += right[3][3];

    return left;
}

inline Matrix& operator -=(Matrix& left, Matrix& right)
{
    left[0][0] -= right[0][0];
    left[0][1] -= right[0][1];
    left[0][2] -= right[0][2];
    left[0][3] -= right[0][3];

    left[1][0] -= right[1][0];
    left[1][1] -= right[1][1];
    left[1][2] -= right[1][2];
    left[1][3] -= right[1][3];

    left[2][0] -= right[2][0];
    left[2][1] -= right[2][1];
    left[2][2] -= right[2][2];
    left[2][3] -= right[2][3];

    left[3][0] -= right[3][0];
    left[3][1] -= right[3][1];
    left[3][2] -= right[3][2];
    left[3][3] -= right[3][3];

    return left;
}

inline Matrix operator +(Matrix& left, Matrix& right)
{
    return Matrix(
            left[0][0] + right[0][0], left[1][0] + right[1][0], left[2][0] + right[2][0], left[3][0] + right[3][0],
            left[0][1] + right[0][1], left[1][1] + right[1][1], left[2][1] + right[2][1], left[3][1] + right[3][1],
            left[0][2] + right[0][2], left[1][2] + right[1][2], left[2][2] + right[2][2], left[3][2] + right[3][2],
            left[0][3] + right[0][3], left[1][3] + right[1][3], left[2][3] + right[2][3], left[3][3] + right[3][3]);
}

inline Matrix operator -(Matrix& left, Matrix& right)
{
    return Matrix(
            left[0][0] - right[0][0], left[1][0] - right[1][0], left[2][0] - right[2][0], left[3][0] - right[3][0],
            left[0][1] - right[0][1], left[1][1] - right[1][1], left[2][1] - right[2][1], left[3][1] - right[3][1],
            left[0][2] - right[0][2], left[1][2] - right[1][2], left[2][2] - right[2][2], left[3][2] - right[3][2],
            left[0][3] - right[0][3], left[1][3] - right[1][3], left[2][3] - right[2][3], left[3][3] - right[3][3]);
}

inline Matrix operator *(Matrix& left, float right)
{
    return Matrix(
            left[0][0] * right, left[1][0] * right, left[2][0] * right, left[3][0] * right,
            left[0][1] * right, left[1][1] * right, left[2][1] * right, left[3][1] * right,
            left[0][2] * right, left[1][2] * right, left[2][2] * right, left[3][2] * right,
            left[0][3] * right, left[1][3] * right, left[2][3] * right, left[3][3] * right);
}

inline Matrix operator *(Matrix& left, Matrix& right)
{
    return Matrix(
            left[0][0] * right[0][0], left[1][0] * right[1][0], left[2][0] * right[2][0], left[3][0] * right[3][0],
            left[0][1] * right[0][1], left[1][1] * right[1][1], left[2][1] * right[2][1], left[3][1] * right[3][1],
            left[0][2] * right[0][2], left[1][2] * right[1][2], left[2][2] * right[2][2], left[3][2] * right[3][2],
            left[0][3] * right[0][3], left[1][3] * right[1][3], left[2][3] * right[2][3], left[3][3] * right[3][3]);
}

inline Matrix operator *(float left, Matrix& right)
{
    return Matrix(
            left * right[0][0], left * right[1][0], left * right[2][0], left * right[3][0],
            left * right[0][1], left * right[1][1], left * right[2][1], left * right[3][1],
            left * right[0][2], left * right[1][2], left * right[2][2], left * right[3][2],
            left * right[0][3], left * right[1][3], left * right[2][3], left * right[3][3]);
}

inline Matrix& operator *=(Matrix& left, float right)
{
    left[0][0] += right;
    left[0][1] += right;
    left[0][2] += right;
    left[0][3] += right;

    left[1][0] += right;
    left[1][1] += right;
    left[1][2] += right;
    left[1][3] += right;

    left[2][0] += right;
    left[2][1] += right;
    left[2][2] += right;
    left[2][3] += right;

    left[3][0] += right;
    left[3][1] += right;
    left[3][2] += right;
    left[3][3] += right;

    return left;
}

inline Matrix& operator *=(Matrix& left, Matrix& right)
{
    left[0][0] *= right[0][0];
    left[0][1] *= right[0][1];
    left[0][2] *= right[0][2];
    left[0][3] *= right[0][3];

    left[1][0] *= right[1][0];
    left[1][1] *= right[1][1];
    left[1][2] *= right[1][2];
    left[1][3] *= right[1][3];

    left[2][0] *= right[2][0];
    left[2][1] *= right[2][1];
    left[2][2] *= right[2][2];
    left[2][3] *= right[2][3];

    left[3][0] *= right[3][0];
    left[3][1] *= right[3][1];
    left[3][2] *= right[3][2];
    left[3][3] *= right[3][3];

    return left;
}

inline Matrix operator /(Matrix& left, Matrix& right)
{
    return Matrix(
            left[0][0] / right[0][0], left[1][0] / right[1][0], left[2][0] / right[2][0], left[3][0] / right[3][0],
            left[0][1] / right[0][1], left[1][1] / right[1][1], left[2][1] / right[2][1], left[3][1] / right[3][1],
            left[0][2] / right[0][2], left[1][2] / right[1][2], left[2][2] / right[2][2], left[3][2] / right[3][2],
            left[0][3] / right[0][3], left[1][3] / right[1][3], left[2][3] / right[2][3], left[3][3] / right[3][3]);
}

inline Matrix operator /(Matrix& left, float right)
{
    const float oneOver = 1.0f / right;
    return Matrix(
            left[0][0] * oneOver, left[1][0] * oneOver, left[2][0] * oneOver, left[3][0] * oneOver,
            left[0][1] * oneOver, left[1][1] * oneOver, left[2][1] * oneOver, left[3][1] * oneOver,
            left[0][2] * oneOver, left[1][2] * oneOver, left[2][2] * oneOver, left[3][2] * oneOver,
            left[0][3] * oneOver, left[1][3] * oneOver, left[2][3] * oneOver, left[3][3] * oneOver);
}

inline Matrix& operator /=(Matrix& left, float right)
{
    const float oneOver = 1.0f / right;

    left[0][0] *= oneOver;
    left[0][1] *= oneOver;
    left[0][2] *= oneOver;
    left[0][3] *= oneOver;

    left[1][0] *= oneOver;
    left[1][1] *= oneOver;
    left[1][2] *= oneOver;
    left[1][3] *= oneOver;

    left[2][0] *= oneOver;
    left[2][1] *= oneOver;
    left[2][2] *= oneOver;
    left[2][3] *= oneOver;

    left[3][0] *= oneOver;
    left[3][1] *= oneOver;
    left[3][2] *= oneOver;
    left[3][3] *= oneOver;

    return left;
}

inline Matrix& operator /=(Matrix& left, Matrix& right)
{
    left[0][0] /= right[0][0];
    left[0][1] /= right[0][1];
    left[0][2] /= right[0][2];
    left[0][3] /= right[0][3];

    left[1][0] /= right[1][0];
    left[1][1] /= right[1][1];
    left[1][2] /= right[1][2];
    left[1][3] /= right[1][3];

    left[2][0] /= right[2][0];
    left[2][1] /= right[2][1];
    left[2][2] /= right[2][2];
    left[2][3] /= right[2][3];

    left[3][0] /= right[3][0];
    left[3][1] /= right[3][1];
    left[3][2] /= right[3][2];
    left[3][3] /= right[3][3];

    return left;
}

inline bool operator ==(Matrix& left, Matrix& right)
{
    return (left[0][0] == right[0][0]) && (left[1][0] == right[1][0]) && left[2][0] == right[2][0] && left[3][0] == right[3][0] &&
           (left[0][1] == right[0][1]) && (left[1][1] == right[1][1]) && left[2][1] == right[2][1] && left[3][1] == right[3][1] &&
           (left[0][2] == right[0][2]) && (left[1][2] == right[1][2]) && left[2][2] == right[2][2] && left[3][2] == right[3][2] &&
           (left[0][3] == right[0][3]) && (left[1][3] == right[1][3]) && left[2][3] == right[2][3] && left[3][3] == right[3][3];
}

inline bool operator !=(Matrix& left, Matrix& right)
{
    return (left[0][0] != right[0][0]) || (left[1][0] != right[1][0]) || left[2][0] != right[2][0] || left[3][0] != right[3][0] ||
           (left[0][1] != right[0][1]) || (left[1][1] != right[1][1]) || left[2][1] != right[2][1] || left[3][1] != right[3][1] ||
           (left[0][2] != right[0][2]) || (left[1][2] != right[1][2]) || left[2][2] != right[2][2] || left[3][2] != right[3][2] ||
           (left[0][3] != right[0][3]) || (left[1][3] != right[1][3]) || left[2][3] != right[2][3] || left[3][3] != right[3][3];
}
