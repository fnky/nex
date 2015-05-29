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
inline T Quaternion<T>::length() const
{
    return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

template <typename T>
inline T Quaternion<T>::lengthSquared() const
{
    return (x * x) + (y * y) + (z * z) + (w * w);
}

template <typename T>
inline void Quaternion<T>::normalize()
{
    const T oneOverLength = static_cast<T>(1.0) / length();
    x *= oneOverLength;
    y *= oneOverLength;
    z *= oneOverLength;
    w *= oneOverLength;
}

template <typename T>
inline void Quaternion<T>::conjugate()
{
    x = -x;
    y = -y;
    z = -z;
}

template <typename T>
inline Quaternion<T> Quaternion<T>::normalize(const Quaternion<T>& value)
{
    const T oneOverLength = static_cast<T>(1.0) / value.length();

    Quaternion<T> result;

    result.x *= oneOverLength;
    result.y *= oneOverLength;
    result.z *= oneOverLength;
    result.w *= oneOverLength;

    return result;
}

template <typename T>
inline Quaternion<T> Quaternion<T>::conjugate(const Quaternion<T>& value)
{
    Quaternion<T> result;

    result.x = -value.x;
    result.y = -value.y;
    result.z = -value.z;
    result.w = value.w;

    return result;
}

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

template <typename T>
inline Quaternion<T>& operator *=(Quaternion<T>& left, const T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;
    left.w *= right;

    return left;
}


template <typename T>
inline Quaternion<T>& operator *=(Quaternion<T>& left, const Quaternion<T>& right)
{
    const T crossA = (left.y * right.z - left.z * right.y);
    const T crossB = (left.z * right.x - left.x * right.z);
    const T crossC =  (left.x * right.y - left.y * right.x);
    const T crossD = (left.x * right.x + left.y * right.y + left.z * right.z);

    left.x = (left.x * right.w + right.x * left.w) + crossA;
    left.y = (left.y *  right.w + right.y * left.w) + crossB;
    left.z = (left.z * right.w + right.z * left.w) + crossC;
    left.w = left.w * right.w - crossD;

    return left;
}


template <typename T>
inline Quaternion<T> operator /(const Quaternion<T>& left, const Quaternion<T>& right)
{
    const T oneOverSquareLength = 1.0f / (right.x * right.x + right.y * right.y + right.z * right.z + right.w * right.w);

    const T scalarX = -right.x * oneOverSquareLength;
    const T scalarY = -right.y * oneOverSquareLength;
    const T scalarZ = -right.z * oneOverSquareLength;
    const T scalarW = right.w * oneOverSquareLength;

    const T xAdd = (left.y * scalarZ - left.z * scalarY);
    const T yAdd = (left.z * scalarX - left.x * scalarZ);
    const T zAdd = (left.x * scalarY - left.y * scalarX);
    const T distance = (left.x * scalarX + left.y * scalarY + left.z * scalarZ);

    Quaternion<T> result;

    result.x = (left.x * scalarW + scalarX * left.w) + xAdd;
    result.y = (left.y * scalarW + scalarY * left.w) + yAdd;
    result.z = (left.z * scalarW + scalarZ * left.w) + zAdd;
    result.w = left.w * scalarW - distance;

    return result;
}

template <typename T>
inline Quaternion<T>& operator /=(Quaternion<T>& left, const Quaternion<T>& right)
{
    const T oneOverSquareLength = 1.0f / (right.x * right.x + right.y * right.y + right.z * right.z + right.w * right.w);

    const T scalarX = -right.x * oneOverSquareLength;
    const T scalarY = -right.y * oneOverSquareLength;
    const T scalarZ = -right.z * oneOverSquareLength;
    const T scalarW = right.w * oneOverSquareLength;

    const T xAdd = (left.y * scalarZ - left.z * scalarY);
    const T yAdd = (left.z * scalarX - left.x * scalarZ);
    const T zAdd = (left.x * scalarY - left.y * scalarX);
    const T distance = (left.x * scalarX + left.y * scalarY + left.z * scalarZ);

    left.x = (left.x * scalarW + scalarX * left.w) + xAdd;
    left.y = (left.y * scalarW + scalarY * left.w) + yAdd;
    left.z = (left.z * scalarW + scalarZ * left.w) + zAdd;
    left.w = left.w * scalarW - distance;

    return left;
}

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
