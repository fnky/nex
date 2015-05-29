#include <cmath>

template <typename T>
inline Quaternion::Quaternion() :
    x(static_cast<T>(0.0)),
    y(static_cast<T>(0.0)),
    z(static_cast<T>(0.0)),
    w(static_cast<T>(1.0))
{ }

template <typename T>
inline Quaternion::Quaternion(const T x, const T y, const T z, const T w) :
    x(x),
    y(y),
    z(z),
    w(w)
{ }
