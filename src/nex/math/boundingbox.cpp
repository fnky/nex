#include <nex/math/boundingbox.h>

namespace nx
{

BoundingBox::BoundingBox(const vec3f min, const vec3f max) :
    min(min),
    max(max)
{ }

} //namespace nx
