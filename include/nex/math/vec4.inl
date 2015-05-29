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
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;
    const T deltaZ = z - other.z;
    const T deltaW = w - other.w;

    return sqrtf(
                (deltaX * deltaX) +
                (deltaY * deltaY) +
                (deltaZ * deltaZ) +
                (deltaW * deltaW));
}

template <typename T>
inline T Vec4<T>::distanceSquared(const Vec4<T>& other) const
{
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;
    const T deltaZ = z - other.z;
    const T deltaW = w - other.w;

    return (deltaX * deltaX) +
           (deltaY * deltaY) +
           (deltaZ * deltaZ) +
           (deltaW * deltaW);
}

template <typename T>
inline T Vec4<T>::dot(const Vec4<T>& other) const
{
    return (x * other.x) +
           (y * other.y) +
           (z * other.z) +
           (w * other.w);
}

template <typename T>
inline void Vec4<T>::normalize()
{
  const T oneOverLength = 1.0f / length();
  x *= oneOverLength;
  y *= oneOverLength;
  z *= oneOverLength;
  w *= oneOverLength;
}

template <typename T>
inline T Vec4<T>::distance(const Vec4<T>& left, const Vec4<T>& right)
{
    const T deltaX = left.x - right.x;
    const T deltaY = left.y - right.y;
    const T deltaZ = left.z - right.z;
    const T deltaW = left.w - right.w;

    return sqrtf(
                (deltaX * deltaX) +
                (deltaY * deltaY) +
                (deltaZ * deltaZ) +
                (deltaW * deltaW));
}

template <typename T>
inline T Vec4<T>::distanceSquared(const Vec4<T>& left, const Vec4<T>& right)
{
    const T deltaX = left.x - right.x;
    const T deltaY = left.y - right.y;
    const T deltaZ = left.z - right.z;
    const T deltaW = left.w - right.w;

    return (deltaX * deltaX) +
           (deltaY * deltaY) +
           (deltaZ * deltaZ) +
           (deltaW * deltaW);
}

template <typename T>
inline T Vec4<T>::dot(const Vec4<T>& left, const Vec4<T>& right)
{
    return (left.x * right.x) +
           (left.y * right.y) +
           (left.z * right.z) +
           (left.w * right.w);
}

template <typename T>
inline Vec4<T> Vec4<T>::normalize(const Vec4<T>& value)
{
    const T oneOverLength = 1.0f / value.length();

    Vec4<T> result;

    result.x *= oneOverLength;
    result.y *= oneOverLength;
    result.z *= oneOverLength;
    result.w *= oneOverLength;

    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::min(const Vec4<T>& left, const Vec4<T>& right)
{
    Vec4<T> result;
    result.x = left.x < right.x ? left.x : right.x;
    result.y = left.y < right.y ? left.y : right.y;
    result.z = left.z < right.z ? left.z : right.z;
    result.w = left.w < right.w ? left.w : right.w;
    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::max(const Vec4<T>& left, const Vec4<T>& right)
{
    Vec4<T> result;
    result.x = left.x > right.x ? left.x : right.x;
    result.y = left.y > right.y ? left.y : right.y;
    result.z = left.z > right.z ? left.z : right.z;
    result.w = left.w > right.w ? left.w : right.w;
    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::clamp(const Vec4<T>& value, const Vec4<T>& min, const Vec4<T>& max)
{
    const float valueX = value.x;
    const float minX = valueX > max.x ? max.x : valueX;
    const float resultX =  minX < min.x ? min.x : minX;

    const float valueY = value.y;
    const float minY = valueY > max.y ? max.y : valueY;
    const float resultY =  minY < min.y ? min.y : minY;

    const float valueZ = value.z;
    const float minZ = valueZ > max.z ? max.z : valueZ;
    const float resultZ = minZ < min.z ? min.z : minZ;

    const float valueW = value.w;
    const float minW = valueW > max.w ? max.w : valueW;
    const float resultW = minW < min.w ? min.w : minW;

    Vec4<T> result;
    result.x = resultX;
    result.y = resultY;
    result.z = resultZ;
    result.w = resultW;
    return result;
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
