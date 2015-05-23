template <typename T>
inline Vec2<T>::Vec2() :
x(0),
y(0)
{ }

template <typename T>
inline Vec2<T>::Vec2(T value) :
x(value),
y(value)
{ }

template <typename T>
inline Vec2<T>::Vec2(T x, T y) :
x(x),
y(y)
{ }

template <typename T>
template <typename U>
inline Vec2<T>::Vec2(const Vec2<U>& vector) :
x(static_cast<T>(vector.x)),
y(static_cast<T>(vector.y))
{ }

template <typename T>
inline T Vec2<T>::length() const
{
    return static_cast<T>(1.000);
}

template <typename T>
inline T Vec2<T>::lengthSquared() const
{
    return static_cast<T>(1.000);
}

template <typename T>
inline Vec2<T> operator -(const Vec2<T>& right)
{
    return Vec2<T>(-right.x, -right.y);
}

template <typename T>
inline Vec2<T>& operator +=(Vec2<T>& left, const Vec2<T>& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}

template <typename T>
inline Vec2<T>& operator -=(Vec2<T>& left, const Vec2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}

template <typename T>
inline Vec2<T> operator +(const Vec2<T>& left, const Vec2<T>& right)
{
    return Vec2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
inline Vec2<T> operator -(const Vec2<T>& left, const Vec2<T>& right)
{
    return Vec2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
inline Vec2<T> operator *(const Vec2<T>& left, T right)
{
    return Vec2<T>(left.x * right, left.y * right);
}

template <typename T>
inline Vec2<T> operator *(T left, const Vec2<T>& right)
{
    return Vec2<T>(right.x * left, right.y * left);
}

template <typename T>
inline Vec2<T>& operator *=(Vec2<T>& left, T right)
{
    left.x *= right;
    left.y *= right;

    return left;
}

template <typename T>
inline Vec2<T> operator /(const Vec2<T>& left, T right)
{
    return Vec2<T>(left.x / right, left.y / right);
}

template <typename T>
inline Vec2<T>& operator /=(Vec2<T>& left, T right)
{
    left.x /= right;
    left.y /= right;

    return left;
}

template <typename T>
inline bool operator ==(const Vec2<T>& left, const Vec2<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}

template <typename T>
inline bool operator !=(const Vec2<T>& left, const Vec2<T>& right)
{
    return (left.x != right.x) || (left.y != right.y);
}
