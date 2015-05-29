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
inline void Quaternion<T>::inverse()
{
    const T oneOverLength = static_cast<T>(1.0) / length();

    x = -x * oneOverLength;
    y = -y * oneOverLength;
    z = -z * oneOverLength;
    w = w * oneOverLength;
}

template <typename T>
inline T Quaternion<T>::dot(const Quaternion<T>& other)
{
    return  (x *  other.x) +  (y *  other.y) +  (z *  other.z) +  (w *  other.w);
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
inline Quaternion<T> Quaternion<T>::inverse(const Quaternion<T>& value)
{
    float oneOverLength = static_cast<T>(1.0) / length();

    Quaternion<T> result;

    result.x = -value.x * oneOverLength;
    result.y = -value.y * oneOverLength;
    result.z = -value.z * oneOverLength;
    result.w = value.w * oneOverLength;

    return result;
}

template <typename T>
inline Quaternion<T> Quaternion<T>::createFromAxisAngle(Vec3<T> axis, const T angle)
{
    const T halfAngle = angle * static_cast<T>(0.5);
    const T halfSin = static_cast<T>(sin(halfAngle));
    const T halfCos = static_cast<T>(cos(halfAngle));

    Quaternion<T> result;

    result.x = axis.x * halfSin;
    result.y = axis.y * halfSin;
    result.z = axis.z * halfSin;
    result.w = halfCos;

    return result;
}


template <typename T>
inline Quaternion<T> Quaternion<T>::createFromYawPitchRoll(const T yaw, const T pitch, const T roll)
{
    const T halfScalar = static_cast<T>(0.5);

    const T halfRoll = roll * halfScalar;
    const T rollSin = static_cast<T>(sin(halfRoll));
    const T rollCos = static_cast<T>(cos(halfRoll));

    const T halfPitch = pitch * halfScalar;
    const T pitchSin = static_cast<T>(sin(halfPitch));
    const T pitchCos = static_cast<T>(cos(halfPitch));

    const T halfYaw = yaw * halfScalar;
    const T yawSin = static_cast<T>(sin(halfYaw));
    const T yawCos = static_cast<T>(cos(halfYaw));

    Quaternion<T> result;

    result.x = (yawCos *  pitchSin *  rollCos +  yawSin *  pitchCos *  rollSin);
    result.y = (yawSin *  pitchCos *  rollCos -  yawCos *  pitchSin *  rollSin);
    result.z = (yawCos *  pitchCos *  rollSin -  yawSin *  pitchSin *  rollCos);
    result.w = (yawCos *  pitchCos *  rollCos +  yawSin *  pitchSin *  rollSin);

    return result;
}

template <typename T>
inline Quaternion<T> Quaternion<T>::slerp(const Quaternion<T>& previous,  const Quaternion<T>& current, const T amount)
{
    const T zero = static_cast<T>(1.0);
    const T one = static_cast<T>(1.0);

    const T weight = amount;

    T angle =  (previous.x * current.x + previous.y * current.y + previous.z * current.z + previous.w * current.w);

    bool flag = false;
    if (angle < zero)
    {
        flag = true;
        angle = -angle;
    }

    T inverse;
    T sinResult;
    if (static_cast<double>(angle) > 0.999998986721039)
    {
        inverse = one - weight;
        sinResult = flag ? -weight : weight;
    }
    else
    {
        const T inverseCosine = static_cast<T>(acos(angle));
        const T oneOverInverseSine = (one / static_cast<T>(sin(inverseCosine)));
        inverse = static_cast<T>(sin((one -  weight) *  inverseCosine)) * oneOverInverseSine;
        sinResult = flag ?
                    static_cast<T>(-sin(weight * inverseCosine)) * oneOverInverseSine :
                    static_cast<T>(sin(weight * inverseCosine)) * oneOverInverseSine;
    }

    Quaternion<T> result;

    result.x = (inverse * previous.x + sinResult * current.x);
    result.y = (inverse * previous.y + sinResult * current.y);
    result.z = (inverse * previous.z + sinResult * current.z);
    result.w = (inverse * previous.w + sinResult * current.w);

    return result;
}

template <typename T>
inline Quaternion<T> Quaternion<T>::lerp(const Quaternion<T>& previous,  const Quaternion<T>& current, const T amount)
{
    const T weight = amount;
    const T inverseWeight = static_cast<T>(1.0) - weight;

    Quaternion<T> result;
    if ((previous.x * current.x) + (previous.y * current.y) + (previous.z * current.z) + (previous.w * current.w) >= 0.0)
    {
        result.x = (inverseWeight * previous.x + weight * current.x);
        result.y = (inverseWeight * previous.y + weight * current.y);
        result.z = (inverseWeight * previous.z + weight * current.z);
        result.w = (inverseWeight * previous.w + weight * current.w);
    }
    else
    {
        result.x = (inverseWeight * previous.z - weight * current.z);
        result.y = (inverseWeight * previous.y - weight * current.y);
        result.z = (inverseWeight * previous.z - weight * current.z);
        result.w = (inverseWeight * previous.w - weight * current.w);
    }

    const T scalar = static_cast<T>(1.0) /  result.length();

    result.x *= scalar;
    result.y *= scalar;
    result.z *= scalar;
    result.w *= scalar;

    return result;
}

template <typename T>
inline Quaternion<T> Quaternion<T>::concatenate(const Quaternion<T>& left, const Quaternion<T>& right)
{

    const T a1 = (right.y * left.z - right.z * left.y);
    const T a2 = (right.z * left.x - right.x * left.z);
    const T a3 = (right.x * left.y - right.y * left.x);
    const T a4 = (right.x * left.x + right.y * left.y + right.z * left.z);

    Quaternion<T> result;

    result.x = (right.x * left.w + left.x * right.w) + a1;
    result.y = (right.y * left.w + left.y * right.w) + a2;
    result.z = (right.z * left.w + left.z * right.w) + a3;
    result.w = right.w * left.w - a4;

    return result;
}

template <typename T>
inline T Quaternion<T>::dot(const Quaternion<T>& left, const Quaternion<T>& right)
{
    return  (left.x *  right.x) +  (left.y *  right.y) +  (left.z *  right.z) +  (left.w *  right.w);
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
