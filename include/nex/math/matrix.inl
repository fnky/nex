/*
    IF YOU DON'T KNOW MATRIX MATH, DON'T TOUCH THIS STUFF.
    PLEASE AND THANK YOU.
*/

//TODO (Tyler): Make this class type agnostic.

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

inline Matrix::Matrix(
       const float m11, const float m21, const float m31, const float m41,
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

inline Matrix::col_type& Matrix::operator[] (const uint32 index)
{
    return m[index];
}

inline const Matrix::col_type&  Matrix::operator[] (const uint32 index) const
{
    return m[index];
}

inline Matrix Matrix::translate(const vec3f& position)
{
    Matrix matrix;

    matrix[0][0] = 1.0f;
    matrix[0][1] = 0.0f;
    matrix[0][2] = 0.0f;
    matrix[0][3] = 0.0f;

    matrix[1][0] = 0.0f;
    matrix[1][1] = 1.0f;
    matrix[1][2] = 0.0f;
    matrix[1][3] = 0.0f;

    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = 1.0f;
    matrix[2][3] = 0.0f;

    matrix[3][0] = position.x;
    matrix[3][1] = position.y;
    matrix[3][2] = position.z;
    matrix[3][3] = 1.0f;

    return matrix;
}

inline Matrix Matrix::scale(const float xScale, const float yScale, const float zScale)
{
    Matrix matrix;

    matrix[0][0] = xScale;
    matrix[0][1] = 0.0f;
    matrix[0][2] = 0.0f;
    matrix[0][3] = 0.0f;

    matrix[1][0] = 0.0f;
    matrix[1][1] = yScale;
    matrix[1][2] = 0.0f;
    matrix[1][3] = 0.0f;

    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = zScale;
    matrix[2][3] = 0.0f;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;

    return matrix;
}

inline Matrix Matrix::rotateX(const float radians)
{
    const float cosResult = cosf(radians);
    const float sinResult = sinf(radians);

    Matrix matrix;

    matrix[0][0] = 1.0f;
    matrix[0][1] = 0.0f;
    matrix[0][2] = 0.0f;
    matrix[0][3] = 0.0f;

    matrix[1][0] = 0.0f;
    matrix[1][1] = cosResult;
    matrix[1][2] = sinResult;
    matrix[1][3] = 0.0f;

    matrix[2][0] = 0.0f;
    matrix[2][1] = -sinResult;
    matrix[2][2] = cosResult;
    matrix[2][3] = 0.0f;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;

    return matrix;
}

inline Matrix Matrix::rotateY(const float radians)
{
    const float cosResult = cosf(radians);
    const float sinResult = sinf(radians);

    Matrix matrix;

    matrix[0][0] = cosResult;
    matrix[0][1] = 0.0f;
    matrix[0][2] = -sinResult;
    matrix[0][3] = 0.0f;

    matrix[1][0] = 0.0f;
    matrix[1][1] = 1.0f;
    matrix[1][2] = 0.0f;
    matrix[1][3] = 0.0f;

    matrix[2][0] = sinResult;
    matrix[2][1] = 0.0f;
    matrix[2][2] = cosResult;
    matrix[2][3] = 0.0f;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;

    return matrix;
}

inline Matrix Matrix::rotateZ(const float radians)
{
    const float cosResult = cosf(radians);
    const float sinResult = sinf(radians);

    Matrix matrix;

    matrix[0][0] = cosResult;
    matrix[0][1] = sinResult;
    matrix[0][2] = 0.0f;
    matrix[0][3] = 0.0f;

    matrix[1][0] = -sinResult;
    matrix[1][1] = cosResult;
    matrix[1][2] = 0.0f;
    matrix[1][3] = 0.0f;

    matrix[2][0] = 0.0f;
    matrix[2][1] = 0.0f;
    matrix[2][2] = 1.0f;
    matrix[2][3] = 0.0f;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;

    return matrix;
}

inline Matrix Matrix::createFromAxisAngle(const vec3f& axis, const float angle)
{
    const float xRotation = axis.x;
    const float yRotation = axis.y;
    const float zRotation = axis.z;

    const float sinResult = sinf(angle);
    const float cosResult = cosf(angle);

    const float xRotationSquared = xRotation * xRotation;
    const float yRotationSquared = yRotation * yRotation;
    const float zRotationSquared = zRotation * zRotation;

    const float dotA = xRotation * yRotation;
    const float dotB = xRotation * zRotation;
    const float dotC = yRotation * zRotation;

    Matrix matrix;

    matrix[0][0] = xRotationSquared + cosResult * (1.0f - xRotationSquared);
    matrix[0][1] = (dotA - cosResult * dotA + sinResult * zRotation);
    matrix[0][2] = (dotB - cosResult * dotB - sinResult * yRotation);
    matrix[0][3] = 0.0f;

    matrix[1][0] = (dotA - cosResult * dotA - sinResult * zRotation);
    matrix[1][1] = yRotationSquared + cosResult * (1.0f - yRotationSquared);
    matrix[1][2] = (dotC - cosResult * dotC + sinResult * xRotation);
    matrix[1][3] = 0.0f;

    matrix[2][0] = (dotB - cosResult * dotB + sinResult * yRotation);
    matrix[2][1] = (dotC -  cosResult * dotC - sinResult * xRotation);
    matrix[2][2] = zRotationSquared + cosResult * (1.0f - zRotationSquared);
    matrix[2][3] = 0.0f;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;

    return matrix;
}

inline Matrix Matrix::frustum(
        const float left,
        const float right,
        const float bottom,
        const float top,
        const float nearVal,
        const float farVal
    )
{
    Matrix result;
    result[0][0] = (2.0f * nearVal) / (right - left);
    result[1][1] = (2.0f * nearVal) / (top - bottom);
    result[2][0] = (right + left) / (right - left);
    result[2][1] = (top + bottom) / (top - bottom);
    result[2][2] = -(farVal + nearVal) / (farVal - nearVal);
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * farVal * nearVal) / (farVal - nearVal);
    return result;
}

inline Matrix Matrix::perspective(
        const float fovy,
        const float aspect,
        const float zNear,
        const float zFar)
{
    float tanHalfFovy = tanf(fovy * 0.5f);

    Matrix result;
    result[0][0] = 1.0f / (aspect * tanHalfFovy);
    result[1][1] = 1.0f / (tanHalfFovy);
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    return result;
}

inline Matrix Matrix::perspectiveFov(
        const float fov,
        const float width,
        const float height,
        const float zNear,
        const float zFar)
{
    float const rad = fov;
    float const h = cosf(0.5f * rad) / sinf(0.5f * rad);
    float const w = h * height / width;

    Matrix result;
    result[0][0] = w;
    result[1][1] = h;
    result[2][2] = - (zFar + zNear) / (zFar - zNear);
    result[2][3] = -1.0f;
    result[3][2] = - (2.0f * zFar * zNear) / (zFar - zNear);
    return result;
}

inline Matrix Matrix::orthographic(
        const float width,
        const float height,
        const float zNearPlane,
        const float zFarPlane)
{
    Matrix matrix;
    matrix[0][0] = 2.0f / width;
    matrix[0][1] = matrix[0][2] = matrix[0][3] = 0.0f;
    matrix[1][1] = 2.0f / height;
    matrix[2][0] = matrix[1][2] = matrix[1][3] = 0.0f;
    matrix[2][2] = (1.0f / (zNearPlane - zFarPlane));
    matrix[2][0] = matrix[2][1] = matrix[2][3] = 0.0f;
    matrix[3][0] = matrix[3][1] = 0.0f;
    matrix[3][2] = zNearPlane / (zNearPlane - zFarPlane);
    matrix[3][3] = 1.0f;
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

inline Matrix& operator +=(Matrix& left, const Matrix& right)
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

inline Matrix& operator -=(Matrix& left, const Matrix& right)
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

inline Matrix operator +(const Matrix& left, const Matrix& right)
{
    return Matrix(
            left[0][0] + right[0][0], left[1][0] + right[1][0], left[2][0] + right[2][0], left[3][0] + right[3][0],
            left[0][1] + right[0][1], left[1][1] + right[1][1], left[2][1] + right[2][1], left[3][1] + right[3][1],
            left[0][2] + right[0][2], left[1][2] + right[1][2], left[2][2] + right[2][2], left[3][2] + right[3][2],
            left[0][3] + right[0][3], left[1][3] + right[1][3], left[2][3] + right[2][3], left[3][3] + right[3][3]);
}

inline Matrix operator -(const Matrix& left, const Matrix& right)
{
    return Matrix(
            left[0][0] - right[0][0], left[1][0] - right[1][0], left[2][0] - right[2][0], left[3][0] - right[3][0],
            left[0][1] - right[0][1], left[1][1] - right[1][1], left[2][1] - right[2][1], left[3][1] - right[3][1],
            left[0][2] - right[0][2], left[1][2] - right[1][2], left[2][2] - right[2][2], left[3][2] - right[3][2],
            left[0][3] - right[0][3], left[1][3] - right[1][3], left[2][3] - right[2][3], left[3][3] - right[3][3]);
}

inline Matrix operator *(const Matrix& left, const float right)
{
    return Matrix(
            left[0][0] * right, left[1][0] * right, left[2][0] * right, left[3][0] * right,
            left[0][1] * right, left[1][1] * right, left[2][1] * right, left[3][1] * right,
            left[0][2] * right, left[1][2] * right, left[2][2] * right, left[3][2] * right,
            left[0][3] * right, left[1][3] * right, left[2][3] * right, left[3][3] * right);
}

inline Matrix operator *(const Matrix& left, const Matrix& right)
{
    return Matrix(
            left[0][0] * right[0][0], left[1][0] * right[1][0], left[2][0] * right[2][0], left[3][0] * right[3][0],
            left[0][1] * right[0][1], left[1][1] * right[1][1], left[2][1] * right[2][1], left[3][1] * right[3][1],
            left[0][2] * right[0][2], left[1][2] * right[1][2], left[2][2] * right[2][2], left[3][2] * right[3][2],
            left[0][3] * right[0][3], left[1][3] * right[1][3], left[2][3] * right[2][3], left[3][3] * right[3][3]);
}

inline Matrix operator *(const float left, const Matrix& right)
{
    return Matrix(
            left * right[0][0], left * right[1][0], left * right[2][0], left * right[3][0],
            left * right[0][1], left * right[1][1], left * right[2][1], left * right[3][1],
            left * right[0][2], left * right[1][2], left * right[2][2], left * right[3][2],
            left * right[0][3], left * right[1][3], left * right[2][3], left * right[3][3]);
}

// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
//            | 2 5 8 |    |  2  6 10 14 |
//                         |  3  7 11 15 |
inline Vector4 Matrix4::operator*(const Vector4& rhs) const
{
    return Vector4(m[0]*rhs.x + m[4]*rhs.y + m[8]*rhs.z  + m[12]*rhs.w,
                   m[1]*rhs.x + m[5]*rhs.y + m[9]*rhs.z  + m[13]*rhs.w,
                   m[2]*rhs.x + m[6]*rhs.y + m[10]*rhs.z + m[14]*rhs.w,
                   m[3]*rhs.x + m[7]*rhs.y + m[11]*rhs.z + m[15]*rhs.w);
}



inline Vector3 Matrix4::operator*(const Vector3& rhs) const
{
    return Vector3(m[0]*rhs.x + m[4]*rhs.y + m[8]*rhs.z,
                   m[1]*rhs.x + m[5]*rhs.y + m[9]*rhs.z,
                   m[2]*rhs.x + m[6]*rhs.y + m[10]*rhs.z);
}

inline Matrix& operator *=(Matrix& left, const float right)
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

inline Matrix& operator *=(Matrix& left, const Matrix& right)
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

inline Matrix operator /(const Matrix& left, const Matrix& right)
{
    return Matrix(
            left[0][0] / right[0][0], left[1][0] / right[1][0], left[2][0] / right[2][0], left[3][0] / right[3][0],
            left[0][1] / right[0][1], left[1][1] / right[1][1], left[2][1] / right[2][1], left[3][1] / right[3][1],
            left[0][2] / right[0][2], left[1][2] / right[1][2], left[2][2] / right[2][2], left[3][2] / right[3][2],
            left[0][3] / right[0][3], left[1][3] / right[1][3], left[2][3] / right[2][3], left[3][3] / right[3][3]);
}

inline Matrix operator /(const Matrix& left, const float right)
{
    const float oneOver = 1.0f / right;
    return Matrix(
            left[0][0] * oneOver, left[1][0] * oneOver, left[2][0] * oneOver, left[3][0] * oneOver,
            left[0][1] * oneOver, left[1][1] * oneOver, left[2][1] * oneOver, left[3][1] * oneOver,
            left[0][2] * oneOver, left[1][2] * oneOver, left[2][2] * oneOver, left[3][2] * oneOver,
            left[0][3] * oneOver, left[1][3] * oneOver, left[2][3] * oneOver, left[3][3] * oneOver);
}

inline Matrix& operator /=(Matrix& left, const float right)
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

inline Matrix& operator /=(Matrix& left, const Matrix& right)
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

inline bool operator ==(const Matrix& left, const Matrix& right)
{
    return (left[0][0] == right[0][0]) && (left[1][0] == right[1][0]) && left[2][0] == right[2][0] && left[3][0] == right[3][0] &&
           (left[0][1] == right[0][1]) && (left[1][1] == right[1][1]) && left[2][1] == right[2][1] && left[3][1] == right[3][1] &&
           (left[0][2] == right[0][2]) && (left[1][2] == right[1][2]) && left[2][2] == right[2][2] && left[3][2] == right[3][2] &&
           (left[0][3] == right[0][3]) && (left[1][3] == right[1][3]) && left[2][3] == right[2][3] && left[3][3] == right[3][3];
}

inline bool operator !=(const Matrix& left, const Matrix& right)
{
    return (left[0][0] != right[0][0]) || (left[1][0] != right[1][0]) || left[2][0] != right[2][0] || left[3][0] != right[3][0] ||
           (left[0][1] != right[0][1]) || (left[1][1] != right[1][1]) || left[2][1] != right[2][1] || left[3][1] != right[3][1] ||
           (left[0][2] != right[0][2]) || (left[1][2] != right[1][2]) || left[2][2] != right[2][2] || left[3][2] != right[3][2] ||
           (left[0][3] != right[0][3]) || (left[1][3] != right[1][3]) || left[2][3] != right[2][3] || left[3][3] != right[3][3];
}
