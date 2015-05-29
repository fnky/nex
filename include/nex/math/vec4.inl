#include <cmath>

template <typename T>
inline Vec4<T>::Vec4() :
    x(0),
    y(0),
    z(0),
    w(0)
{ }

template <typename T>
inline Vec4<T>::Vec4(T value) :
    x(value),
    y(value),
    z(value),
    w(value)
{ }

template <typename T>
inline Vec4<T>::Vec4(T x, T y, T z, T w) :
    x(x),
    y(y),
    z(z),
    w(w)
{ }

template <typename T>
template <typename U>
inline Vec4<T>::Vec4(const Vec4<U>& vector) :
    x(static_cast<T>(vector.x)),
    y(static_cast<T>(vector.y)),
    z(static_cast<T>(vector.z)),
    w(static_cast<T>(vector.w))
{ }


template <typename T>
inline T Vec4<T>::length() const
{
    return sqrtf((x * x) + (y * y) +  (z * z) +  (w * w));
}

template <typename T>
inline T Vec4<T>::lengthSquared() const
{
    return (x * x) + (y * y) +  (z * z) +  (w * w);
}

template <typename T>
inline T Vec4<T>::distance(const Vec4<T>& other) const
{
    const float deltaX = x - other.x;
    const float deltaY = y - other.y;
    const float deltaZ = z - other.z;
    const float deltaW = w - other.w;

    return sqrtf(
                (deltaX * deltaX) +
                (deltaY * deltaY) +
                (deltaZ * deltaZ) +
                (deltaW * deltaW));
}

template <typename T>
inline T Vec4<T>::distanceSquared(const Vec4<T>& other) const
{
    const float deltaX = x - other.x;
    const float deltaY = y - other.y;
    const float deltaZ = z - other.z;
    const float deltaW = w - other.w;

    return (deltaX * deltaX) +
           (deltaY * deltaY) +
           (deltaZ * deltaZ) +
           (deltaW * deltaW);
}

template <typename T>
inline float Vec4<T>::distance(const Vec4<T>& left, const Vec4<T>& right)
{
    const float deltaX = left.x - right.x;
    const float deltaY = left.y - right.y;
    const float deltaZ = left.z - right.z;
    const float deltaW = left.w - right.w;

    return sqrtf(
                (deltaX * deltaX) +
                (deltaY * deltaY) +
                (deltaZ * deltaZ) +
                (deltaW * deltaW));
}

template <typename T>
inline float Vec4<T>::distanceSquared(const Vec4<T>& left, const Vec4<T>& right)
{
    const float deltaX = left.x - right.x;
    const float deltaY = left.y - right.y;
    const float deltaZ = left.z - right.z;
    const float deltaW = left.w - right.w;

    return (deltaX * deltaX) +
           (deltaY * deltaY) +
           (deltaZ * deltaZ) +
           (deltaW * deltaW);
}

template <typename T>
inline Vec4<T> operator -(const Vec4<T>& right)
{
    return Vec4<T>(-right.x, -right.y, -right.z, -right.w);
}

template <typename T>
inline Vec4<T> operator +(const Vec4<T>& left, const Vec4<T>& right)
{
    return Vec4<T>(left.x + right.x,
                   left.y + right.y,
                   left.z + right.z,
                   left.w + right.w);
}

template <typename T>
inline Vec4<T>& operator +=(Vec4<T>& left, const Vec4<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    left.w += right.w;

    return left;
}

template <typename T>
inline Vec4<T> operator -(const Vec4<T>& left, const Vec4<T>& right)
{
    return Vec4<T>(left.x - right.x,
                   left.y - right.y,
                   left.z - right.z,
                   left.w - right.w);
}

template <typename T>
inline Vec4<T>& operator -=(Vec4<T>& left, const Vec4<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    left.w -= right.z;

    return left;
}

template <typename T>
inline Vec4<T> operator *(const Vec4<T>& left, const T right)
{
    return Vec4<T>(left.x * right,
                   left.y * right,
                   left.z * right,
                   left.w * right);
}

template <typename T>
inline Vec4<T> operator *(const Vec4<T>& left, const Vec4<T>& right)
{
    return Vec4<T>(left.x * right.x,
                   left.y * right.y,
                   left.z * right.z,
                   left.w * right.w);
}

template <typename T>
inline Vec4<T> operator *(const T left, const Vec4<T>& right)
{
    return Vec4<T>(right.x * left,
                   right.y * left,
                   right.z * left,
                   right.w * left);
}

template <typename T>
inline Vec4<T>& operator *=(Vec4<T>& left, const T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;
    left.w *= right;

    return left;
}

template <typename T>
inline Vec4<T>& operator *=(Vec4<T>& left, const Vec4<T>& right)
{
    left.x *= right.x;
    left.y *= right.y;
    left.z *= right.z;
    left.w *= right.w;

    return left;
}

template <typename T>
inline Vec4<T> operator /(const Vec4<T>& left, const Vec4<T>& right)
{
    return Vec4<T>(left.x / right.x,
                   left.y / right.y,
                   left.z / right.z,
                   left.w / right.w);
}

template <typename T>
inline Vec4<T> operator /(const Vec4<T>& left, const T right)
{
    const T oneOver = static_cast<T>(1.0) / right;
    return Vec4<T>(left.x * oneOver,
                   left.y * oneOver,
                   left.z * oneOver,
                   left.w * oneOver);
}

template <typename T>
inline Vec4<T>& operator /=(Vec4<T>& left, const T right)
{
    const T oneOver = static_cast<T>(1.0) / right;

    left.x *= oneOver;
    left.y *= oneOver;
    left.z *= oneOver;
    left.w *= oneOver;

    return left;
}

template <typename T>
inline Vec4<T>& operator /=(Vec4<T>& left, const Vec4<T>& right)
{
    left.x /= right.x;
    left.y /= right.y;
    left.z /= right.z;
    left.w /= right.w;

    return left;
}

template <typename T>
inline bool operator ==(const Vec4<T>& left, const Vec4<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
}

template <typename T>
inline bool operator !=(const Vec4<T>& left, const Vec4<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z) || (left.w != right.w);
}
