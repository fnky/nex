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
inline T Vec3<T>::distance(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    const T deltaX = vectorA.x - vectorB.x;
    const T deltaY = vectorA.y - vectorB.y;
    const T deltaZ = vectorA.z - vectorB.z;

    return static_cast<T>(std::sqrt((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ)));
}

template <typename T>
inline T Vec3<T>::distance(const Vec3<T>& other) const
{
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;
    const T deltaZ = z - other.z;

    return static_cast<T>(std::sqrt((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ)));
}

template <typename T>
inline T Vec3<T>::distanceSquared(const Vec3<T>& other) const
{
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;
    const T deltaZ = z - other.z;

    return static_cast<T>((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ));
}

template <typename T>
inline T Vec3<T>::distanceSquared(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    const T deltaX = vectorA.x - vectorB.x;
    const T deltaY = vectorA.y - vectorB.y;
    const T deltaZ = vectorA.z - vectorB.z;

    return static_cast<T>((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ));
}

template <typename T>
inline T Vec3<T>::dot(const Vec3<T>& other) const
{
    return (x * other.x) + (y * other.y) + (z * other.z);
}

template <typename T>
inline T Vec3<T>::dot(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    return (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y) + (vectorA.z * vectorB.z);
}

template <typename T>
inline void Vec3<T>::normalize()
{
    const T l = static_cast<T>(1.0) / length();
    x *= l;
    y *= l;
    z *= l;
}

template <typename T>
inline Vec3<T> Vec3<T>::normalize(const Vec3<T>& vector)
{
    const T l = static_cast<T>(1.0) / vector.length();
    return Vec3<T>(vector.x * l,
                   vector.y * l,
                   vector.z * l);
}

template <typename T>
inline Vec3<T> Vec3<T>::cross(const Vec3<T>& other) const
{
    Vec3<T> result;
    result.x = (y * other.z) - (z * other.y);
    result.y = (z * other.x) - (x * other.z);
    result.z = (x * other.y) - (y * other.x);
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::cross(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    Vec3<T> result;
    result.x = (vectorA.y * vectorB.z) - (vectorA.z * vectorB.y);
    result.y = (vectorA.z * vectorB.x) - (vectorA.x * vectorB.z);
    result.z = (vectorA.x * vectorB.y) - (vectorA.y * vectorB.x);
    return result;
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
