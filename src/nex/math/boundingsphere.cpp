#include <nex/math/boundingsphere.h>

namespace nx
{

BoundingSphere::BoundingSphere(const vec3f center, const float radius) :
    center(center),
    radius(radius)
{ }

} //namespace nx
