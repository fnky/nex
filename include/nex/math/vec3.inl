#include <cmath>

template <typename T>
inline Vec3<T>::Vec3() :
x(0),
y(0),
z(0)
{ }

template <typename T>
inline Vec3<T>::Vec3(T value) :
x(value),
y(value),
z(value)
{ }

template <typename T>
inline Vec3<T>::Vec3(T x, T y, T z) :
x(x),
y(y),
z(z)
{ }

template <typename T>
template <typename U>
inline Vec3<T>::Vec3(const Vec3<U>& vector) :
x(static_cast<T>(vector.x)),
y(static_cast<T>(vector.y)),
z(static_cast<T>(vector.z))
{ }

template <typename T>
inline T Vec3<T>::length() const
{
    return static_cast<T>(std::sqrt(x * x + y * y + z * z));
}


template <typename T>
inline T Vec3<T>::lengthSquared() const
{
    return x * x + y * y + z * z;
}

template <typename T>
inline Vec3<T> operator -(const Vec3<T>& right)
{
    return Vec3<T>(-right.x, -right.y, -right.z);
}

template <typename T>
inline Vec3<T>& operator +=(Vec3<T>& left, const Vec3<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;

    return left;
}

template <typename T>
inline Vec3<T>& operator -=(Vec3<T>& left, const Vec3<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;

    return left;
}

template <typename T>
inline Vec3<T> operator +(const Vec3<T>& left, const Vec3<T>& right)
{
    return Vec3<T>(left.x + right.x,
                   left.y + right.y,
                   left.z + right.z);
}

template <typename T>
inline Vec3<T> operator -(const Vec3<T>& left, const Vec3<T>& right)
{
    return Vec3<T>(left.x - right.x,
                   left.y - right.y,
                   left.z - right.z);
}

template <typename T>
inline Vec3<T> operator *(const Vec3<T>& left, T right)
{
    return Vec3<T>(left.x * right,
                   left.y * right,
                   left.z * right);
}

template <typename T>
inline Vec3<T> operator *(const Vec3<T>& left, const Vec3<T>& right)
{
    return Vec3<T>(left.x * right.x,
                   left.y * right.y,
                   left.z * right.z);
}

template <typename T>
inline Vec3<T> operator *(T left, const Vec3<T>& right)
{
    return Vec3<T>(right.x * left,
                   right.y * left,
                   right.z * left);
}

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
    return Vec3<T>(left.x / right,
                   left.y / right,
                   left.z / right);
}

template <typename T>
inline Vec3<T>& operator /=(Vec3<T>& left, T right)
{
    left.x /= right;
    left.y /= right;
    left.z /= right;

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

template <typename T>
inline bool operator ==(const Vec3<T>& left, const Vec3<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

template <typename T>
inline bool operator !=(const Vec3<T>& left, const Vec3<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}
