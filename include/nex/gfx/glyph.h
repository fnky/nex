#ifndef GLYPH_H_INCLUDE
#define GLYPH_H_INCLUDE
#include <nex/system/typedefs.h>
#include <nex/math/rect.h>

namespace nx
{

struct Glyph
{
    Glyph() :
        advance(0)
    {}

    real32 advance;

    rectf bounds;
    recti textureRect;
};

} // namespace nx

#endif // GLYPH_H_INCLUDE
