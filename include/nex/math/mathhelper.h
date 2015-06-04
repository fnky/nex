#ifndef MATHHELPER_H_INCLUDE
#define MATHHELPER_H_INCLUDE

namespace nx
{

/**
 * @brief Represents the mathematical constant e.
 */
const float E = 2.718282f;

/**
 * @brief Represents the log base two of e.
 */
const float Log2E = 1.442695f;

/**
* @brief Represents the log base ten of e.
*/
const float Log10E = 0.4342945f;

/**
 * @brief Represents the value of pi
 */
const float Pi = 3.141593f;

/**
 * @brief Represents the value of pi times two.
 */
const float TwoPi = 6.283185f;

/**
 * @brief Represents the value of pi divided by two.
 */
const float PiOver2 = 1.570796f;

/**
 * @brief Represents the value of pi divided by four.
 */
const float PiOver4 = 0.7853982f;

/**
 * @brief Convert degrees into radians.
 * @param degrees = value.
 * @return radians.
 */
inline float toRadians(const float degrees)
{
    return degrees * Pi / 180.0f;
}

/**
 * @brief Convert radians to degrees.
 * @param radians = value.
 * @return degrees.
 */
inline float toDegrees(const float radians)
{
    return  radians * 180.0f / Pi;
}

/**
 * @brief Returns the lesser of two values.
 * @param left = Source value.
 * @param right = Source value.
 * @return the least value.
 */
inline float min(const float left, const float right)
{
  return left < right ? left : right;
}

/**
 * @brief Returns the greater of two values.
 * @param left = Source value.
 * @param right = Source value.
 * @return the greater value.
 */
inline float max(const float left, const float right)
{
    return left > right ? left : right;
}

/**
 * @brief Restricts a value to be within a specified range.
 * @param value = The value to clamp.
 * @param min = The minimum value. If value is less than min, min will be returned.
 * @param max = The maximum value. If value is greater than max, max will be returned.
 * @return the clamped value.
 */
inline float clamp(float value, const float min, const float max)
{
  value = value > max ? max : value;
  value = value < min ? min : value;
  return value;
}

/**
 * @brief Linearly interpolates between two values.
 * @param previous = previous value.
 * @param current = current value.
 * @param amount = the interpolation weight.
 * @return the interpolated value.
 */
inline float lerp(const float previous, const float current, const float amount)
{
    return previous + (current - previous) * amount;
}

} //namespace nx

#endif // MATHHELPER_H_INCLUDE
