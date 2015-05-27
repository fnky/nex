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
