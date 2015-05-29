#include <nex/math/plane.h>

namespace nx
{

Plane::Plane(vec3f normal, float distance) :
    normal(normal),
    distance(distance)
{ }

} //namespace nx
