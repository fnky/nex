/*
    IF YOU DON'T KNOW MATRIX MATH, DON'T TOUCH THIS STUFF.
    PLEASE AND THANK YOU.
*/


template <typename T>
inline Matrix<T>::Matrix()
{
    //Create an identity matrix.

    const T zero = static_cast<T>(0.0);
    const T one = static_cast<T>(1.0);

    m[0][0] = one;
    m[0][1] = zero;
    m[0][2] = zero;
    m[0][3] = zero;

    m[1][0] = zero;
    m[1][1] = one;
    m[1][2] = zero;
    m[1][3] = zero;

    m[2][0] = zero;
    m[2][1] = zero;
    m[2][2] = one;
    m[2][3] = zero;

    m[3][0] = zero;
    m[3][1] = zero;
    m[3][2] = zero;
    m[3][3] = one;
}

template <typename T>
inline Matrix<T>::Matrix(
       const T m11, const T m21, const T m31, const T m41,
       const T m12, const T m22, const T m32, const T m42,
       const T m13, const T m23, const T m33, const T m43,
       const T m14, const T m24, const T m34, const T m44)
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



template <typename T>
inline Matrix<T> Matrix<T>::translate(const Vec3<T>& position)
{
    const T zero = static_cast<T>(0.0);
    const T one = static_cast<T>(1.0);

    Matrix<T> matrix;

    matrix[0][0] = one;
    matrix[0][1] = zero;
    matrix[0][2] = zero;
    matrix[0][3] = zero;

    matrix[1][0] = zero;
    matrix[1][1] = one;
    matrix[1][2] = zero;
    matrix[1][3] = zero;

    matrix[2][0] = zero;
    matrix[2][1] = zero;
    matrix[2][2] = one;
    matrix[2][3] = zero;

    matrix[3][0] = position.x;
    matrix[3][1] = position.y;
    matrix[3][2] = position.z;
    matrix[3][3] = one;

    return matrix;
}

template <typename T>
inline Matrix<T> Matrix<T>::scale(const T xScale, const T yScale, const T zScale)
{
    const T zero = static_cast<T>(0.0);
    const T one = static_cast<T>(1.0);

    Matrix<T> matrix;

    matrix[0][0] = xScale;
    matrix[0][1] = zero;
    matrix[0][2] = zero;
    matrix[0][3] = zero;

    matrix[1][0] = zero;
    matrix[1][1] = yScale;
    matrix[1][2] = zero;
    matrix[1][3] = zero;

    matrix[2][0] = zero;
    matrix[2][1] = zero;
    matrix[2][2] = zScale;
    matrix[2][3] = zero;

    matrix[3][0] = zero;
    matrix[3][1] = zero;
    matrix[3][2] = zero;
    matrix[3][3] = one;

    return matrix;
}

template <typename T>
inline Matrix<T> Matrix<T>::rotateX(const T radians)
{
    const T cosResult = static_cast<T>(cos(radians));
    const T sinResult = static_cast<T>(sin(radians));

    const T zero = static_cast<T>(0.0);
    const T one = static_cast<T>(1.0);

    Matrix<T> matrix;

    matrix[0][0] = one;
    matrix[0][1] = zero;
    matrix[0][2] = zero;
    matrix[0][3] = zero;

    matrix[1][0] = zero;
    matrix[1][1] = cosResult;
    matrix[1][2] = sinResult;
    matrix[1][3] = zero;

    matrix[2][0] = zero;
    matrix[2][1] = -sinResult;
    matrix[2][2] = cosResult;
    matrix[2][3] = zero;

    matrix[3][0] = zero;
    matrix[3][1] = zero;
    matrix[3][2] = zero;
    matrix[3][3] = one;

    return matrix;
}

template <typename T>
inline Matrix<T> Matrix<T>::rotateY(const T radians)
{
    const T cosResult = static_cast<T>(cos(radians));
    const T sinResult = static_cast<T>(sin(radians));

    const T zero = static_cast<T>(0.0);
    const T one = static_cast<T>(1.0);

    Matrix<T> matrix;

    matrix[0][0] = cosResult;
    matrix[0][1] = zero;
    matrix[0][2] = -sinResult;
    matrix[0][3] = zero;

    matrix[1][0] = zero;
    matrix[1][1] = one;
    matrix[1][2] = zero;
    matrix[1][3] = zero;

    matrix[2][0] = sinResult;
    matrix[2][1] = zero;
    matrix[2][2] = cosResult;
    matrix[2][3] = zero;

    matrix[3][0] = zero;
    matrix[3][1] = zero;
    matrix[3][2] = zero;
    matrix[3][3] = one;

    return matrix;
}

template <typename T>
inline Matrix<T> Matrix<T>::rotateZ(const T radians)
{
    const T cosResult = static_cast<T>(cos(radians));
    const T sinResult = static_cast<T>(sin(radians));

    const T zero = static_cast<T>(0.0);
    const T one = static_cast<T>(1.0);

    Matrix<T> matrix;

    matrix[0][0] = cosResult;
    matrix[0][1] = sinResult;
    matrix[0][2] = zero;
    matrix[0][3] = zero;

    matrix[1][0] = -sinResult;
    matrix[1][1] = cosResult;
    matrix[1][2] = zero;
    matrix[1][3] = zero;

    matrix[2][0] = zero;
    matrix[2][1] = zero;
    matrix[2][2] = one;
    matrix[2][3] = zero;

    matrix[3][0] = zero;
    matrix[3][1] = zero;
    matrix[3][2] = zero;
    matrix[3][3] = one;

    return matrix;
}

template <typename T>
inline Matrix<T> Matrix<T>::createFromAxisAngle(const Vec3<T>& axis, const T angle)
{
    const T xRotation = axis.x;
    const T yRotation = axis.y;
    const T zRotation = axis.z;

    const T sinResult = static_cast<T>(sin(angle));
    const T cosResult = static_cast<T>(cos(angle));

    const T xRotationSquared = xRotation * xRotation;
    const T yRotationSquared = yRotation * yRotation;
    const T zRotationSquared = zRotation * zRotation;

    const T dotA = xRotation * yRotation;
    const T dotB = xRotation * zRotation;
    const T dotC = yRotation * zRotation;

    const T zero = static_cast<T>(0.0);
    const T one = static_cast<T>(1.0);

    Matrix<T> matrix;

    matrix[0][0] = xRotationSquared + cosResult * (one - xRotationSquared);
    matrix[0][1] = (dotA - cosResult * dotA + sinResult * zRotation);
    matrix[0][2] = (dotB - cosResult * dotB - sinResult * yRotation);
    matrix[0][3] = zero;

    matrix[1][0] = (dotA - cosResult * dotA - sinResult * zRotation);
    matrix[1][1] = yRotationSquared + cosResult * (one - yRotationSquared);
    matrix[1][2] = (dotC - cosResult * dotC + sinResult * xRotation);
    matrix[1][3] = zero;

    matrix[2][0] = (dotB - cosResult * dotB + sinResult * yRotation);
    matrix[2][1] = (dotC -  cosResult * dotC - sinResult * xRotation);
    matrix[2][2] = zRotationSquared + cosResult * (one - zRotationSquared);
    matrix[2][3] = zero;

    matrix[3][0] = zero;
    matrix[3][1] = zero;
    matrix[3][2] = zero;
    matrix[3][3] = one;

    return matrix;
}

template <typename T>
inline Matrix<T> Matrix<T>::frustum(
        const T left,
        const T right,
        const T bottom,
        const T top,
        const T nearVal,
        const T farVal
    )
{
    const T one = static_cast<T>(1.0);
    const T two = static_cast<T>(2.0);

    Matrix<T> result;
    result[0][0] = (two * nearVal) / (right - left);
    result[1][1] = (two * nearVal) / (top - bottom);
    result[2][0] = (right + left) / (right - left);
    result[2][1] = (top + bottom) / (top - bottom);
    result[2][2] = -(farVal + nearVal) / (farVal - nearVal);
    result[2][3] = -one;
    result[3][2] = -(two * farVal * nearVal) / (farVal - nearVal);
    return result;
}

template <typename T>
inline Matrix<T> Matrix<T>::perspective(
        const T fovy,
        const T aspect,
        const T zNear,
        const T zFar)
{
    const T tanHalfFovy = static_cast<T>(tan(fovy * static_cast<T>(0.5)));

    const T one = static_cast<T>(1.0);
    const T two = static_cast<T>(2.0);

    Matrix<T> result;
    result[0][0] = one / (aspect * tanHalfFovy);
    result[1][1] = one / (tanHalfFovy);
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -one;
    result[3][2] = -(two * zFar * zNear) / (zFar - zNear);
    return result;
}

template <typename T>
inline Matrix<T> Matrix<T>::perspectiveFov(
        const T fov,
        const T width,
        const T height,
        const T zNear,
        const T zFar)
{

    const T half = static_cast<T>(0.5);

    const T rad = fov;
    const T h = static_cast<T>(cos(half * rad)) / static_cast<T>(sin(half * rad));
    const T w = h * height / width;

    Matrix<T> result;
    result[0][0] = w;
    result[1][1] = h;
    result[2][2] = - (zFar + zNear) / (zFar - zNear);
    result[2][3] = -static_cast<T>(1.0);
    result[3][2] = - (static_cast<T>(2.0) * zFar * zNear) / (zFar - zNear);
    return result;
}

template <typename T>
inline Matrix<T> Matrix<T>::orthographic(
        const T width,
        const T height,
        const T zNearPlane,
        const T zFarPlane)
{
    const T zero = static_cast<T>(0.0);
    const T one = static_cast<T>(1.0);
    const T two = static_cast<T>(2.0);

    Matrix<T> matrix;
    matrix[0][0] = two / width;
    matrix[0][1] = matrix[0][2] = matrix[0][3] = zero;
    matrix[1][1] = two / height;
    matrix[2][0] = matrix[1][2] = matrix[1][3] = zero;
    matrix[2][2] = (one / (zNearPlane - zFarPlane));
    matrix[2][0] = matrix[2][1] = matrix[2][3] = zero;
    matrix[3][0] = matrix[3][1] = zero;
    matrix[3][2] = zNearPlane / (zNearPlane - zFarPlane);
    matrix[3][3] = one;
    return matrix;
}

template <typename T>
inline Matrix<T> Matrix<T>::lookAt(const Vec3<T>& eye, const Vec3<T>& center, const Vec3<T>& up)
{
    Vec3<T> const f(Vec3<T>::normalize(center - eye));
    Vec3<T> const s(Vec3<T>::normalize(Vec3<T>::cross(f, up)));
    Vec3<T> const u(Vec3<T>::cross(s, f));

    Matrix<T> result;
    result[0][0] = s.x;
    result[1][0] = s.y;
    result[2][0] = s.z;
    result[0][1] = u.x;
    result[1][1] = u.y;
    result[2][1] = u.z;
    result[0][2] =-f.x;
    result[1][2] =-f.y;
    result[2][2] =-f.z;
    result[3][0] =-Vec3<T>::dot(s, eye);
    result[3][1] =-Vec3<T>::dot(u, eye);
    result[3][2] = Vec3<T>::dot(f, eye);
    return result;
}

template <typename T>
inline Matrix<T> operator -(Matrix<T>& right)
{
    return Matrix<T>(
            -right[0][0], -right[1][0], -right[2][0], -right[3][0],
            -right[0][1], -right[1][1], -right[2][1], -right[3][1],
            -right[0][2], -right[1][2], -right[2][2], -right[3][2],
            -right[0][3], -right[1][3], -right[2][3], -right[3][3]);

}

template <typename T>
inline Matrix<T>& operator +=(Matrix<T>& left, const Matrix<T>& right)
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

template <typename T>
inline Matrix<T>& operator -=(Matrix<T>& left, const Matrix<T>& right)
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

template <typename T>
inline Matrix<T> operator +(const Matrix<T>& left, const Matrix<T>& right)
{
    return Matrix<T>(
            left[0][0] + right[0][0], left[1][0] + right[1][0], left[2][0] + right[2][0], left[3][0] + right[3][0],
            left[0][1] + right[0][1], left[1][1] + right[1][1], left[2][1] + right[2][1], left[3][1] + right[3][1],
            left[0][2] + right[0][2], left[1][2] + right[1][2], left[2][2] + right[2][2], left[3][2] + right[3][2],
            left[0][3] + right[0][3], left[1][3] + right[1][3], left[2][3] + right[2][3], left[3][3] + right[3][3]);
}

template <typename T>
inline Matrix<T> operator -(const Matrix<T>& left, const Matrix<T>& right)
{
    return Matrix<T>(
            left[0][0] - right[0][0], left[1][0] - right[1][0], left[2][0] - right[2][0], left[3][0] - right[3][0],
            left[0][1] - right[0][1], left[1][1] - right[1][1], left[2][1] - right[2][1], left[3][1] - right[3][1],
            left[0][2] - right[0][2], left[1][2] - right[1][2], left[2][2] - right[2][2], left[3][2] - right[3][2],
            left[0][3] - right[0][3], left[1][3] - right[1][3], left[2][3] - right[2][3], left[3][3] - right[3][3]);
}

template <typename T>
inline Matrix<T> operator *(const Matrix<T>& left, const T right)
{
    return Matrix<T>(
            left[0][0] * right, left[1][0] * right, left[2][0] * right, left[3][0] * right,
            left[0][1] * right, left[1][1] * right, left[2][1] * right, left[3][1] * right,
            left[0][2] * right, left[1][2] * right, left[2][2] * right, left[3][2] * right,
            left[0][3] * right, left[1][3] * right, left[2][3] * right, left[3][3] * right);
}

template <typename T>
inline Matrix<T> operator *(const Matrix<T>& left, const Matrix<T>& right)
{
    return Matrix<T>(
            left[0][0] * right[0][0], left[1][0] * right[1][0], left[2][0] * right[2][0], left[3][0] * right[3][0],
            left[0][1] * right[0][1], left[1][1] * right[1][1], left[2][1] * right[2][1], left[3][1] * right[3][1],
            left[0][2] * right[0][2], left[1][2] * right[1][2], left[2][2] * right[2][2], left[3][2] * right[3][2],
            left[0][3] * right[0][3], left[1][3] * right[1][3], left[2][3] * right[2][3], left[3][3] * right[3][3]);
}

template <typename T>
inline Matrix<T> operator *(const T left, const Matrix<T>& right)
{
    return Matrix<T>(
            left * right[0][0], left * right[1][0], left * right[2][0], left * right[3][0],
            left * right[0][1], left * right[1][1], left * right[2][1], left * right[3][1],
            left * right[0][2], left * right[1][2], left * right[2][2], left * right[3][2],
            left * right[0][3], left * right[1][3], left * right[2][3], left * right[3][3]);
}

// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
//            | 2 5 8 |    |  2  6 10 14 |
//                         |  3  7 11 15 |
/*template <typename T>
inline Vector4 Matrix4::operator*(const Vector4& rhs) const
{
    return Vector4(m[0]*rhs.x + m[4]*rhs.y + m[8]*rhs.z  + m[12]*rhs.w,
                   m[1]*rhs.x + m[5]*rhs.y + m[9]*rhs.z  + m[13]*rhs.w,
                   m[2]*rhs.x + m[6]*rhs.y + m[10]*rhs.z + m[14]*rhs.w,
                   m[3]*rhs.x + m[7]*rhs.y + m[11]*rhs.z + m[15]*rhs.w);
}

template <typename T>
inline Vector3 Matrix4::operator*(const Vector3& rhs) const
{
    return Vector3(m[0]*rhs.x + m[4]*rhs.y + m[8]*rhs.z,
                   m[1]*rhs.x + m[5]*rhs.y + m[9]*rhs.z,
                   m[2]*rhs.x + m[6]*rhs.y + m[10]*rhs.z);
}
*/
template <typename T>
inline Matrix<T>& operator *=(Matrix<T>& left, const T right)
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

template <typename T>
inline Matrix<T>& operator *=(Matrix<T>& left, const Matrix<T>& right)
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

template <typename T>
inline Matrix<T> operator /(const Matrix<T>& left, const Matrix<T>& right)
{
    return Matrix<T>(
            left[0][0] / right[0][0], left[1][0] / right[1][0], left[2][0] / right[2][0], left[3][0] / right[3][0],
            left[0][1] / right[0][1], left[1][1] / right[1][1], left[2][1] / right[2][1], left[3][1] / right[3][1],
            left[0][2] / right[0][2], left[1][2] / right[1][2], left[2][2] / right[2][2], left[3][2] / right[3][2],
            left[0][3] / right[0][3], left[1][3] / right[1][3], left[2][3] / right[2][3], left[3][3] / right[3][3]);
}

template <typename T>
inline Matrix<T> operator /(const Matrix<T>& left, const T right)
{
    const T oneOver = static_cast<T>(1.0) / right;
    return Matrix<T>(
            left[0][0] * oneOver, left[1][0] * oneOver, left[2][0] * oneOver, left[3][0] * oneOver,
            left[0][1] * oneOver, left[1][1] * oneOver, left[2][1] * oneOver, left[3][1] * oneOver,
            left[0][2] * oneOver, left[1][2] * oneOver, left[2][2] * oneOver, left[3][2] * oneOver,
            left[0][3] * oneOver, left[1][3] * oneOver, left[2][3] * oneOver, left[3][3] * oneOver);
}

template <typename T>
inline Matrix<T>& operator /=(Matrix<T>& left, const T right)
{
    const T oneOver = static_cast<T>(1.0) / right;

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

template <typename T>
inline Matrix<T>& operator /=(Matrix<T>& left, const Matrix<T>& right)
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

template <typename T>
inline bool operator ==(const Matrix<T>& left, const Matrix<T>& right)
{
    return (left[0][0] == right[0][0]) && (left[1][0] == right[1][0]) && left[2][0] == right[2][0] && left[3][0] == right[3][0] &&
           (left[0][1] == right[0][1]) && (left[1][1] == right[1][1]) && left[2][1] == right[2][1] && left[3][1] == right[3][1] &&
           (left[0][2] == right[0][2]) && (left[1][2] == right[1][2]) && left[2][2] == right[2][2] && left[3][2] == right[3][2] &&
           (left[0][3] == right[0][3]) && (left[1][3] == right[1][3]) && left[2][3] == right[2][3] && left[3][3] == right[3][3];
}

template <typename T>
inline bool operator !=(const Matrix<T>& left, const Matrix<T>& right)
{
    return (left[0][0] != right[0][0]) || (left[1][0] != right[1][0]) || left[2][0] != right[2][0] || left[3][0] != right[3][0] ||
           (left[0][1] != right[0][1]) || (left[1][1] != right[1][1]) || left[2][1] != right[2][1] || left[3][1] != right[3][1] ||
           (left[0][2] != right[0][2]) || (left[1][2] != right[1][2]) || left[2][2] != right[2][2] || left[3][2] != right[3][2] ||
           (left[0][3] != right[0][3]) || (left[1][3] != right[1][3]) || left[2][3] != right[2][3] || left[3][3] != right[3][3];
}
