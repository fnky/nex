#include <cmath>

template <typename T>
inline Quaternion<T>::Quaternion() :
    x(static_cast<T>(0.0)),
    y(static_cast<T>(0.0)),
    z(static_cast<T>(0.0)),
    w(static_cast<T>(1.0))
{ }

template <typename T>
inline Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w) :
    x(x),
    y(y),
    z(z),
    w(w)
{ }

template <typename T>
template <typename U>
inline Quaternion<T>::Quaternion(const Quaternion<U>& vector) :
    x(static_cast<T>(vector.x)),
    y(static_cast<T>(vector.y)),
    z(static_cast<T>(vector.z)),
    w(static_cast<T>(vector.w))
{ }

template <typename T>
inline Quaternion<T> operator -(const Quaternion<T>& right)
{
    return Quaternion<T>(-right.x, -right.y, -right.z, -right.w);
}

template <typename T>
inline Quaternion<T>& operator +=(Quaternion<T>& left, const Quaternion<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    left.w += right.w;

    return left;
}


template <typename T>
inline Quaternion<T>& operator -=(Quaternion<T>& left, const Quaternion<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    left.w -= right.w;

    return left;
}

template <typename T>
inline Quaternion<T> operator +(const Quaternion<T>& left, const Quaternion<T>& right)
{
    return Quaternion<T>(
                left.x + right.x,
                left.y + right.y,
                left.z + right.z,
                left.w + right.w);
}

template <typename T>
inline Quaternion<T> operator -(const Quaternion<T>& left, const Quaternion<T>& right)
{
    return Quaternion<T>(
                left.x - right.x,
                left.y - right.y,
                left.z - right.z,
                left.w - right.w);
}


template <typename T>
inline Quaternion<T> operator *(const Quaternion<T>& left, const T right)
{
    return Quaternion<T>(
                left.x * right,
                left.y * right,
                left.z * right,
                left.w * right);
}

template <typename T>
inline Quaternion<T> operator *(const Quaternion<T>& left, const Quaternion<T>& right)
{
    const T crossA = (left.y * right.z - left.z * right.y);
    const T crossB = (left.z * right.x - left.x * right.z);
    const T crossC =  (left.x * right.y - left.y * right.x);
    const T crossD = (left.x * right.x + left.y * right.y + left.z * right.z);

    Quaternion<T> result;

    result.x = (left.x * right.w + right.x * left.w) + crossA;
    result.y = (left.y *  right.w + right.y * left.w) + crossB;
    result.z = (left.z * right.w + right.z * left.w) + crossC;
    result.w = left.w * right.w - crossD;

    return result;
}

template <typename T>
inline Quaternion<T> operator *(const T left, const Quaternion<T>& right)
{
    return Quaternion<T>(
                left * right.x,
                left * right.y,
                left * right.z,
                left * right.w);
}

/*
template <typename T>
inline Vec3<T>& operator *=(Vec3<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;

    return left;
}

template <typename T>
inline Vec3<T>& operator *=(Vec3<T>& left, const Vec3<T>& right)
{
    left.x *= right.x;
    left.y *= right.y;
    left.z *= right.z;

    return left;
}

template <typename T>
inline Vec3<T> operator /(const Vec3<T>& left, const Vec3<T>& right)
{
    return Vec3<T>(left.x / right.x,
                   left.y / right.y,
                   left.z / right.z);
}

template <typename T>
inline Vec3<T> operator /(const Vec3<T>& left, T right)
{
    const T oneOver = static_cast<T>(1.0) / right;
    return Vec3<T>(left.x * oneOver,
                   left.y * oneOver,
                   left.z * oneOver);
}

template <typename T>
inline Vec3<T>& operator /=(Vec3<T>& left, T right)
{
    const T oneOver = static_cast<T>(1.0) / right;
    left.x *= oneOver;
    left.y *= oneOver;
    left.z *= oneOver;

    return left;
}

template <typename T>
inline Vec3<T>& operator /=(Vec3<T>& left, const Vec3<T>& right)
{
    left.x /= right.x;
    left.y /= right.y;
    left.z /= right.z;

    return left;
}
*/

template <typename T>
inline bool operator ==(const Quaternion<T>& left, const Quaternion<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
}

template <typename T>
inline bool operator !=(const Quaternion<T>& left, const Quaternion<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z)|| (left.w != right.w);
}
